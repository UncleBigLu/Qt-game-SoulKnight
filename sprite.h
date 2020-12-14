#ifndef SPRITE_H
#define SPRITE_H
#pragma once

#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsView>
#include <QtMath>

class Sprite :public QGraphicsItem
{
public:
    explicit Sprite();
    Sprite(const QString &imgName);
    Sprite(const QString &imgName, const QPointF pos, int maxFNum, int maxRNum, int fLenth, int fHeight);
    // Speed properties
    qreal vel_x = 0.0;
    qreal vel_y = 0.0;
    qreal maxSpeed = 4;
    qreal angle = 0;
    // Returns an estimate of the area painted by the item
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    // Implements the actuall painting
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    bool isMoving() const;
    virtual void getHit(int damage, int effect);
    virtual void die();
    // Life properties
    int maxHP = 1;
    int currentHP = 1;
protected:
    void nextFrame();
    virtual void move(int step);
    unsigned int sinceLastFrame = 0;
    const unsigned int frameUpdateCD = 10;
    virtual void advance(int step) override;

    // Animation control properties
    QPixmap *spriteImage;
    int currentFrame = 0;           // Range from frame 0 to 3
    int maxFrameNum = 4;
    int currentRow = 0;
    int maxRowNum = 2;        // Max row num in the sprite image
    int frameL = 100;         // Lenth of a single frame
    int frameH = 100;         // Height of a single frame

    // Movement properties
    QPointF nextPos;
    QPointF prevPos;


};

bool wallCollidCheck(const Sprite*);


#endif // SPRITE_H
