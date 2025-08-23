// TreeModel.cpp
#include "TreeModel.h"
#include "../item/TreeItem.h"
#include "../util/SettingManager.h"
#include <QDebug>
#include "QDomDocument"
#include "../util/XmlLoaderHelper.h"
#include <QTextStream>
#include <ElaMessageBar.h>
#include <qregularexpression.h>

// 静态成员定义
TreeModel* TreeModel::instance(QObject* parent)
{
    static TreeModel instance(parent ? parent : new QObject());
    return &instance;
}

TreeModel::TreeModel(QObject* parent)
    : QAbstractItemModel(parent)
{
    m_root = new TreeItem("Root", "");
    setupModelData();
}

TreeModel::~TreeModel()
{
    delete m_root;
}

void TreeModel::setupModelData()
{
    int invalidCount = 0;
    int validCount = 0;

    // 调用通用解析函数
    ParsedXmlResult result = loadAndParseXML("ip_loader_path", "ip_list");
    if (!result.isValid) {
        SettingsManager::instance()->setValue("ip_loader_path", ""); // 清除无效路径
        return;
    }

    QDomElement root = result.doc.documentElement();

    // IP 地址正则
    static QRegularExpression re(
            R"(^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)"
    );

    for (QDomElement ipElem = root.firstChildElement("ip");
         !ipElem.isNull();
         ipElem = ipElem.nextSiblingElement("ip")) {

        QString name = ipElem.firstChildElement("name").text().trimmed();
        QString address = ipElem.firstChildElement("address").text().trimmed();

        if (address.isEmpty() || !re.match(address).hasMatch()) {
            invalidCount++;
            continue;
        }

        if (name.isEmpty()) {
            name = QStringLiteral("未知");
        }

        QString displayText = QStringLiteral("%1 (%2)").arg(name).arg(address);
        new TreeItem(displayText, address, m_root);
        validCount++;
    }

    if (invalidCount > 0) {
        ElaMessageBar::warning(ElaMessageBarType::TopRight,
                               QStringLiteral("警告"),
                               QStringLiteral("有 %1 个IP条目格式不合法，已跳过。").arg(invalidCount),
                               SettingsManager::instance()->getValue("message_bar_msec").toInt());
    }

    if (validCount > 0) {
        ElaMessageBar::success(ElaMessageBarType::TopRight,
                               QStringLiteral("成功"),
                               QStringLiteral("加载 %1 个IP地址").arg(validCount),
                               SettingsManager::instance()->getValue("message_bar_msec").toInt());
    } else {
        ElaMessageBar::error(ElaMessageBarType::TopRight,
                             QStringLiteral("失败"),
                             QStringLiteral("未加载到任何有效IP地址"),
                             SettingsManager::instance()->getValue("message_bar_msec").toInt());
    }
}

QVariant TreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());

    if (role == Qt::DisplayRole) {
        return item->getTitle();
    }
    if (role == Qt::CheckStateRole) {
        return item->isChecked() ? Qt::Checked : Qt::Unchecked;
    }

    return QVariant();
}

bool TreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role == Qt::CheckStateRole && index.isValid()) {
        TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
        bool checked = value.toBool();
        item->setChecked(checked);
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    flags |= Qt::ItemIsUserCheckable;
    return flags;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem* parentItem = parent.isValid() ? static_cast<TreeItem*>(parent.internalPointer()) : m_root;
    TreeItem* childItem = parentItem->getChild(row);
    if (childItem) {
        return createIndex(row, column, childItem);
    }
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
        return QModelIndex();

    TreeItem* childItem = static_cast<TreeItem*>(child.internalPointer());
    TreeItem* parentItem = childItem->getParent();

    if (parentItem == m_root || !parentItem) {
        return QModelIndex();
    }

    return createIndex(parentItem->getRow(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex& parent) const
{
    TreeItem* parentItem = parent.isValid() ? static_cast<TreeItem*>(parent.internalPointer()) : m_root;
    return parentItem->getChildCount();
}

int TreeModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 1;
}

void TreeModel::reloadData() {
    beginResetModel();
    if (m_root) {
        delete m_root;
    }
    m_root = new TreeItem("Root", "");
    setupModelData();
    endResetModel();
}

// TreeModel.cpp 中实现
QList<TreeItem*> TreeModel::getCheckedItems() const
{
    QList<TreeItem*> checkedItems;
    collectCheckedItems(m_root, checkedItems);
    return checkedItems;
}

void TreeModel::collectCheckedItems(TreeItem* parent, QList<TreeItem*>& checkedList) const
{
    if (!parent)
        return;

    for (int i = 0; i < parent->getChildCount(); ++i) {
        TreeItem* child = parent->getChild(i);
        if (child && child->isChecked()) {
            checkedList.append(child);
        }
        // 递归检查子节点
        collectCheckedItems(child, checkedList);
    }
}

void TreeModel::selectAll() {
    bool allChecked = true;
    for (int i = 0; i < m_root->getChildCount(); ++i) {
        TreeItem* child = m_root->getChild(i);
        if (!child || !child->isChecked()) {
            allChecked = false;
            break;
        }
    }

    bool targetChecked = !allChecked;

    for (int i = 0; i < m_root->getChildCount(); ++i) {
        TreeItem* child = m_root->getChild(i);
        if (child && child->isChecked() != targetChecked) {
            child->setChecked(targetChecked);
            QModelIndex idx = index(i, 0);
            emit dataChanged(idx, idx, {Qt::CheckStateRole});
        }
    }
}