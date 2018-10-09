#ifndef EMPLOYEENODEITEM_H
#define EMPLOYEENODEITEM_H

#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QSize>

#define INDENTATION 20
#define HEAD_LABEL_WIDTH 40

namespace Ui {
class EmployeeNodeItem;
}

class EmployeeNodeItem : public QWidget
{
    Q_OBJECT

public:
    EmployeeNodeItem(QWidget *parent = 0);

    ~EmployeeNodeItem();

public:
    void setFullName(const QString& fullName);

    void setSign(const QString& sign);

    void setHeadPixmap(const QPixmap& headPath);

    void setHeadPath(const QString& headPath);

    QSize getHeadLabelSize() const;

    int getIndentation();

    int getLevel();

    void setLevel(int level);

private:
    void initControl();
    QPixmap getRoundImage(const QPixmap &src, QPixmap& mask, QSize masksize);

private:
    void paintEvent(QPaintEvent *event);

private:
    Ui::EmployeeNodeItem *ui;

    // 当前节点缩进距离
    int m_indentation;

    // 当前节点的深度（级数）
    int m_level;

    // 头像Label的宽度
    int m_headLabelWidth;
};

#endif // EMPLOYEENODEITEM_H
