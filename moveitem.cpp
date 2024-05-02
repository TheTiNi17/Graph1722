#include "moveitem.h"

QString int_to_string(int a){
    QString ans="";
    while (a != 0){
        ans  = char(a % 10 + '0') + ans;
        a /= 10;
    }
    return ans;
}

MoveItem::MoveItem(QObject *parent, int k, QString name, QString fname) :
    QObject(parent), QGraphicsItem()
{
    kut = k;
    this->name = name;
    this->fname = fname;
}

MoveItem::~MoveItem()
{

}

QRectF MoveItem::boundingRect() const
{
    return QRectF (-10,-10,40,40);
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawRect(-10,-10,40,40);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    for(auto iter = ((*del)[this]).begin(); ((*del)[this]).end()!= iter; iter++){
        qDebug()<< this->pos();
        painter->setPen(Qt::green);
      painter->drawLine(QPointF(0, 0), (*iter).first->pos() - this->pos());
      painter->setPen(Qt::red);
        painter->drawText(((*iter).first->pos() - this->pos())/2, int_to_string(iter->second));
        painter->setPen(Qt::black);
    }
    painter->drawText(QPointF(-10, 0),name);
    widget->update();
    qDebug()<< del->size();
}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */
    this->setPos(mapToScene(event->pos()));
    //qDebug() << mapToScene(event->pos());
    //qDebug() << event;

}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    qDebug() << this->pos();
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

