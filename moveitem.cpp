#include "moveitem.h"

QString int_to_string(int a){
    QString ans="";
    while (a != 0){
        ans  = char(a % 10 + '0') + ans;
        a /= 10;
    }
    return ans;
}

MoveItem::MoveItem(QObject *parent, int k, QString Name, QString Description) :
    QObject(parent), QGraphicsItem()
{
    kut = k;
    this->Name = Name;
    this->Description = Description;
    //this->setBrush(QBrush(Qt::white));
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
    for(auto iter = ((*del)[this]).begin(); ((*del)[this]).end()!= iter; iter++)
    {
        painter->drawLine(QPointF(0, 0), (*iter).first->pos() - this->pos());
        painter->drawText(((*iter).first->pos() - this->pos())/2, int_to_string(iter->second));
    }
    painter->drawText(QPointF(-10, 0),Name);
    widget->update();
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

