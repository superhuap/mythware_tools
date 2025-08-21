// TreeItem.h
#pragma once

#include <QObject>
#include <QList>

class TreeItem
{
public:
    explicit TreeItem(const QString& title, TreeItem* parent = nullptr);

    ~TreeItem();

    QString getTitle() const;
    void setTitle(const QString& title);

    bool isChecked() const;
    void setChecked(bool checked);

    TreeItem* getParent() const;
    QList<TreeItem*>& getChildren();

    void appendChild(TreeItem* child);
    void removeChild(TreeItem* child);
    int getChildCount() const;
    TreeItem* getChild(int index) const;
    int getRow() const;

private:
    QString m_title;
    bool m_checked = false;
    TreeItem* m_parent = nullptr;
    QList<TreeItem*> m_children;
};