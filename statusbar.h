#ifndef STATUSBAR_H
#define STATUSBAR_H
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QSet>
#include <QGraphicsView>
#include <QtMath>


class StatusBar : public QGraphicsItem
{
public:
    StatusBar();
    QRectF boundingRect() const override;
    // Implements the actuall painting
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    int maxHP = 10;
    int currentHP = 10;
private:
    const int maxLenth;
    const int maxWidth;
    const int margin;

};

#endif // STATUSBAR_H
