#ifndef DEPARTNODEITEM_H
#define DEPARTNODEITEM_H

#include <QLabel>
#include <QPaintEvent>
#include <QPropertyAnimation>

#define INDENTATION 20

class DepartNodeItem : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(int rotation READ rotation WRITE setRotation)
public:
    DepartNodeItem(QWidget *parent = 0);

    ~DepartNodeItem();

    void setText(const QString& title);

    void setExpanded(bool expand);

    int getIndentation();

    void setLevel(int level);

    int getLevel();

private:
    int rotation();

    void setRotation(int rotation);

private:
    void paintEvent(QPaintEvent *event);

private:
    QPropertyAnimation *m_animation;
    // 部门名称
    QString m_name;
    // 部门ID
    QString m_id;
    // 旋转角度
    int m_rotation;
    // 当前节点缩进距离
    int m_indentation;
    // 当前节点的深度（级数）
    int m_level;
};

#endif // DEPARTNODEITEM_H
