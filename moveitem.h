#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QWidget>
#include <QBrush>

class MoveItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    MoveItem(QObject *parent = 0, int k = 0, QString Name = "", QString Description = "");
    int kut = 0;
    QString Name;
    QString Description;
    QMap<MoveItem*, QList<std::pair<MoveItem*, int>>> *PairContainer;
signals:

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:
};

#endif // MOVEITEM_H
