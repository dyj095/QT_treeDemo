#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void onItemExpanded(QTreeWidgetItem * item);
    void onItemCollapsed(QTreeWidgetItem * item);
    void onItemClicked(QTreeWidgetItem * item, int column);

private:
    void initTree();

    QTreeWidgetItem* addChildNode(QTreeWidgetItem *parent, int index, QString namePre);

    QTreeWidgetItem* addChildEmpNode(QTreeWidgetItem *parent, int index);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
