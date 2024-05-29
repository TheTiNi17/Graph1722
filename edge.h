#ifndef EDGE_H
#define EDGE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>
#include <QWidget>
#include <QBrush>
#include <iostream>>

#include "node.h"

class Edge : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    Edge(QObject *parent = 0, Node *Node1 = 0, Node *Node2 = 0, QString Weight = "10");
    void ChangeWeight(QString NewWeight);
    std::string GetWeight();
    bool Contains1(Node *Node);
    bool Contains2(Node *NodeA, Node *NodeB);
    Node *GetNode1() const;
    Node *GetNode2() const;

signals:

private:
    QString Weight;
    Node *Node1;
    Node *Node2;
    //QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public slots:
};

#endif
