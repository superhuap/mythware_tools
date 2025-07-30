// TreeModel.cpp
#include "TreeModel.h"
#include "../item/TreeItem.h"
#include "../util/SettingManager.h"
#include <QFile>
#include <QDebug>
#include <QHostAddress>
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
    m_root = new TreeItem("Root");
    setupModelData();
}

TreeModel::~TreeModel()
{
    delete m_root;
}

void TreeModel::setupModelData()
{
    int invalidCount = 0;
    QFile file(SettingsManager::instance()->getValue("ip_loader_path").toString());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ElaMessageBar::error(ElaMessageBarType::TopRight, "错误", "没有选择ip文件", 2500);
        SettingsManager::instance()->setValue("ip_loader_path", "");
        return ;
    }
    QTextStream in(&file);

    static QRegularExpression re(
        R"(^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)"
    );

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.isEmpty()) {
            continue;
        }
        if (!re.match(line).hasMatch()) {
            invalidCount++;
            continue;
        }
        new TreeItem(line, m_root);
    }
    file.close();
    if (invalidCount > 0) {
        ElaMessageBar::warning(ElaMessageBarType::TopRight, "警告", QString("有 %1 个IP地址格式不合法。").arg(invalidCount), 2500);
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
    m_root = new TreeItem("Root");
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