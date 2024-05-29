#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QWidget>
#include <QBrush>

class Node : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Node(QObject *parent = 0, QString Name = "", QString Description = "");
    void ChangeName(QString Name);
    void ChangeDescription(QString Name);
    std::string GetName();
    std::string GetDescription();

signals:

private:
    QString Name;
    QString Description;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:
};

#endif // NODE_H
