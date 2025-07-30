// TreeModel.h
#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class TreeItem;

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    // 单例获取实例的静态方法
    static TreeModel* instance(QObject* parent = nullptr);

    // 删除拷贝构造和赋值操作符
    TreeModel(const TreeModel&) = delete;
    TreeModel& operator=(const TreeModel&) = delete;

    // 其他模型接口保持不变
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& child) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    void reloadData();
    QList<TreeItem*> getCheckedItems() const;
    void collectCheckedItems(TreeItem *parent, QList<TreeItem *> &checkedList) const;
    void selectAll();

private:
    // 构造和析构设为私有
    explicit TreeModel(QObject* parent = nullptr);
    ~TreeModel();

    void setupModelData();

    TreeItem* m_root;
};