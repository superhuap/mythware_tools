// TreeItem.cpp
#include "TreeItem.h"

TreeItem::TreeItem(const QString& title, TreeItem* parent)
    : m_title(title), m_parent(parent)
{
    if (parent) {
        parent->appendChild(this);
    }
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_children);
}

QString TreeItem::getTitle() const { return m_title; }
void TreeItem::setTitle(const QString& title) { m_title = title; }

bool TreeItem::isChecked() const { return m_checked; }
void TreeItem::setChecked(bool checked)
{
    m_checked = checked;
    // 同步子节点
    for (TreeItem* child : m_children) {
        child->setChecked(checked);
    }
}

TreeItem* TreeItem::getParent() const { return m_parent; }
QList<TreeItem*>& TreeItem::getChildren() { return m_children; }

void TreeItem::appendChild(TreeItem* child) { m_children.append(child); }
void TreeItem::removeChild(TreeItem* child) { m_children.removeOne(child); }
int TreeItem::getChildCount() const { return m_children.size(); }
TreeItem* TreeItem::getChild(int index) const { return m_children.value(index); }
int TreeItem::getRow() const
{
    if (m_parent) {
        return m_parent->getChildren().indexOf(const_cast<TreeItem*>(this));
    }
    return 0;
}