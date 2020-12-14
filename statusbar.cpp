#include "statusbar.h"

StatusBar::StatusBar():
    maxLenth(200), maxWidth(40), margin(5)
{
    setZValue(3);
}

QRectF StatusBar::boundingRect() const
{
    return QRectF(0,0,200,40);
}
void StatusBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);
    painter->drawRect(0, 0, maxLenth, maxWidth);

    painter->setBrush(Qt::red);
    painter->drawRect(margin, margin, (maxLenth-2* margin)*currentHP / maxHP, maxWidth - 2*margin);
}
