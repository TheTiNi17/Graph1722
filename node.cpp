#include "node.h"

Node::Node(QObject *parent, QString Name, QString Description) : QObject(parent), QGraphicsItem()
{
    this->Name = Name;
    this->Description = Description;
}

QRectF Node::boundingRect() const
{
    return QRectF (-10,-10,50,50);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QFont font;
    font.setPointSize(8);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QColor(0, 230, 0));

    painter->drawEllipse(-10,-10,50,50);

    painter->drawText(QPointF(-20, -10), Name);

    widget->update();
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
}

std::string Node::GetName()
{
    return Name.toStdString();
}

std::string Node::GetDescription()
{
    return Description.toStdString();
}

void Node::ChangeName(QString Name)
{
    this->Name = Name;
}

void Node::ChangeDescription(QString Description)
{
    this->Description = Description;
}
