#include "node.h"

Node::Node(QObject *parent, QString Name, QString Description) : QObject(parent), QGraphicsItem()
{
    this->Name = Name;
    this->Description = Description;
}

void Node::ChangeName(QString Name)
{
    this->Name = Name;
}

void Node::ChangeDescription(QString Description)
{
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
    painter->setPen(QPen(Qt::black, 3));

    for (auto i = Edges.begin(); i != Edges.end(); i++)
    {
        painter->drawLine(QPointF(15, 15), i.key()->pos() - this->pos() + QPointF(15, 15));
        painter->drawText(i.key()->pos()/2 - this->pos()/2, i.value());
    }

    painter->setPen(QPen(Qt::black, 1));
    painter->setBrush(QColor(0, 230, 0));


    painter->drawEllipse(-10,-10,50,50);

    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(option);
    Q_UNUSED(widget);

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
    Q_UNUSED(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

bool Node::EdgesContains(Node* node)
{
    return Edges.contains(node);
}

void Node::NewEdge(Node* node, QString weight)
{
    Edges[node] = weight;
}

void Node::RemoveEdge(Node* node)
{
    Edges.remove(node);
}

void Node::RemoveAllEdges()
{
    Edges.clear();
}

std::string Node::GetName()
{
    return Name.toStdString();
}

std::string Node::GetDescription()
{
    return Description.toStdString();
}

QHash <Node*, QString> Node::GetEdges() const
{
    return Edges;
}
