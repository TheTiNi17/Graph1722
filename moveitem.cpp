#include "moveitem.h"


MoveItem::MoveItem(QObject *parent, int k, QString Name, QString Description) :
    QObject(parent), QGraphicsItem()
{
    kut = k;
    this->Name = Name;
    this->Description = Description;
}

QRectF MoveItem::boundingRect() const
{
    return QRectF (-10,-10,50,50);
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QFont font;
    font.setPointSize(8);
    font.setBold(true);
    painter->setFont(font);

    painter->setPen(Qt::black);
    painter->setBrush(QColor(0, 230, 0));
    painter->drawEllipse(-10,-10,50,50);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    for(auto iter = ((*PairContainer)[this]).begin(); ((*PairContainer)[this]).end()!= iter; iter++)
    {
        painter->drawLine(QPointF(0, 0), (*iter).first->pos() - this->pos());
        painter->drawText(((*iter).first->pos() - this->pos())/2, QString::number(iter->second));
    }
    painter->drawText(QPointF(-10, 0),Name);
    widget->update();
}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

