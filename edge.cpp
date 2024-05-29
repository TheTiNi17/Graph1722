#include "edge.h"

Edge::Edge(QObject *parent, Node *Node1, Node *Node2, QString Weight) : QObject(parent), QGraphicsLineItem()
{
    this->Node1 = Node1;
    this->Node2 = Node2;
    this->Weight = Weight;
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QFont font;
    font.setPointSize(8);
    font.setBold(true);
    painter->setFont(font);

    painter->setPen(QPen(Qt::black, 3));
    painter->drawLine(Node1->pos() + QPointF(15, 15), Node2->pos() + QPointF(15, 15));
    painter->drawText((Node1->pos() + QPointF(-10, 0))/2 + (Node2->pos() + QPointF(-10, 0))/2, Weight);

    widget->update();
}

void Edge::ChangeWeight(QString NewWeight)
{
    Weight = NewWeight;
}

std::string Edge::GetWeight()
{
    return Weight.toStdString();
}

bool Edge::Contains1(Node *Node)
{
    if (this->Node1->GetName() == Node->GetName())
    {
        return true;
    }
    if (this->Node2->GetName() == Node->GetName())
    {
        return true;
    }
    return false;
}

bool Edge::Contains2(Node *NodeA, Node *NodeB)
{
    if ((this->Node1->GetName() == NodeA->GetName()) && (this->Node2->GetName() == NodeB->GetName()))
    {
        return true;
    }

    if ((this->Node1->GetName() == NodeB->GetName()) && (this->Node2->GetName() == NodeA->GetName()))
    {
        return true;
    }
    return false;
}

Node* Edge::GetNode1() const
{
    return Node1;
}

Node* Edge::GetNode2() const
{
    return Node2;
}
