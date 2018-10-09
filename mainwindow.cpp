#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "departnodeitem.h"
#include "EmployeeNodeItem.h"

#include <QList>
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onItemExpanded(QTreeWidgetItem *item)
{
    bool bIsChild = item->data(0, Qt::UserRole).toBool();
    if (!bIsChild) {
        DepartNodeItem *departNode = dynamic_cast<DepartNodeItem*>(ui->tree->itemWidget(item, 0));
        if (departNode) {
            departNode->setExpanded(true);
        }
    }
}

void MainWindow::onItemCollapsed(QTreeWidgetItem *item)
{
    bool bIsChild = item->data(0, Qt::UserRole).toBool();
    if (!bIsChild) {
        DepartNodeItem *departNode = dynamic_cast<DepartNodeItem*>(ui->tree->itemWidget(item, 0));
        if (departNode) {
            departNode->setExpanded(false);
        }
    }
}

void MainWindow::onItemClicked(QTreeWidgetItem *item, int column)
{
    bool bIsChild = item->data(0, Qt::UserRole).toBool();
    if (!bIsChild)
    {
        item->setExpanded(!item->isExpanded());
    }
}


void MainWindow::initTree()
{
    ui->tree->setHeaderHidden(true);
    //展开和收缩时信号，以达到变更我三角图片；
    connect(ui->tree, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(onItemClicked(QTreeWidgetItem *, int)));
    connect(ui->tree, SIGNAL(itemExpanded(QTreeWidgetItem *)), this, SLOT(onItemExpanded(QTreeWidgetItem *)));
    connect(ui->tree, SIGNAL(itemCollapsed(QTreeWidgetItem *)), this, SLOT(onItemCollapsed(QTreeWidgetItem *)));
    for(int i = 0; i < 10; i++){
        // 一级部门节点
        QTreeWidgetItem *pRootDeptItem = new QTreeWidgetItem();
        pRootDeptItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
        //设置Data用于区分，Item是分组节点还是子节点，0代表分组节点，1代表子节点
        pRootDeptItem->setData(0, Qt::UserRole, 0);
        DepartNodeItem *pItemName = new DepartNodeItem(ui->tree);
        pItemName->setLevel(0);

        int nMyFriendNum = 6;
        QString qsGroupName = QString("一级部门%3 [%1/%2]").arg(0).arg(nMyFriendNum).arg(i);
        pItemName->setText(qsGroupName);
        //插入分组节点
        ui->tree->addTopLevelItem(pRootDeptItem);
        ui->tree->setItemWidget(pRootDeptItem, 0, pItemName);
        for(int j = 0; j < 5; j++){
            addChildEmpNode(pRootDeptItem, j);
        }
        for(int j = 0; j < 5; j++){
            QString name = QString("二级部门%1").arg(j);
            QTreeWidgetItem *childItem = addChildNode(pRootDeptItem, i * 10 + j,name);
            for(int g = 0; g < 5; g++){
                addChildEmpNode(childItem, g);
            }
        }
    }
}

QTreeWidgetItem* MainWindow::addChildNode(QTreeWidgetItem *parent, int index, QString namePre)
{
    QTreeWidgetItem *pDeptItem = new QTreeWidgetItem();
    pDeptItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
    //设置Data用于区分，Item是分组节点还是子节点，0代表分组节点，1代表子节点
    pDeptItem->setData(0, Qt::UserRole, 0);
    DepartNodeItem *pItemName = new DepartNodeItem(ui->tree);
    int level = 0;
    DepartNodeItem *departNode = dynamic_cast<DepartNodeItem*>(ui->tree->itemWidget(parent, 0));
    if (departNode) {
        level = departNode->getLevel();
        level ++;
    }
    pItemName->setLevel(level);

    int nMyFriendNum = 6;
    QString qsGroupName = QString("%4%3 [%1/%2]").arg(0).arg(nMyFriendNum).arg(index).arg(namePre);
    pItemName->setText(qsGroupName);
    //擦入分组节点
    parent->addChild(pDeptItem);
    ui->tree->setItemWidget(pDeptItem, 0, pItemName);

    return pDeptItem;
}

QTreeWidgetItem *MainWindow::addChildEmpNode(QTreeWidgetItem *parent, int index)
{
    QTreeWidgetItem *pDeptItem = new QTreeWidgetItem();
    //设置Data用于区分，Item是分组节点还是子节点，0代表分组节点，1代表子节点
    pDeptItem->setData(0, Qt::UserRole, 1);
    int level = 0;
    DepartNodeItem *departNode = dynamic_cast<DepartNodeItem*>(ui->tree->itemWidget(parent, 0));
    if (departNode) {
        level = departNode->getLevel();
        level ++;
    }

    EmployeeNodeItem *pItemName = new EmployeeNodeItem(ui->tree);
    pItemName->setLevel(level);
    // 加载本地文件，需要修改成本地的路径
     pItemName->setHeadPath(QString("D:/Qt/workspace/project/QT_treeDemo/images/pic/%1.jpg").arg(index));

    QString qfullName = QString("人员%1").arg(index);
    pItemName->setFullName(qfullName);
    pItemName->setSign(QString("欢迎访问杜燕军工作号-test!!!"));
    //擦入分组节点
    parent->addChild(pDeptItem);
    ui->tree->setItemWidget(pDeptItem, 0, pItemName);
    return pDeptItem;
}
