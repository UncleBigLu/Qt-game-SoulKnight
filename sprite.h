#ifndef SPRITE_H
#define SPRITE_H
#pragma once

#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QSet>
#include <QGraphicsView>


class Sprite :public QGraphicsItem
{
public:
    explicit Sprite();
    // Speed properties
    qreal vel_x = 0.0;
    qreal vel_y = 0.0;
    qreal maxSpeed = 4;
    qreal angle = 0;
    // Returns an estimate of the area painted by the item
    QRectF boundingRect() const override;
    // Implements the actuall painting
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    bool isMoving();

protected:
    void nextFrame();
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
};


class Player:public Sprite{
public:
    // Get keyboard input
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    explicit Player();

    // A reference of view
    QGraphicsView *parentView = nullptr;

private:
    // Update frame and position and other properties.
    void advance(int step) override;
    // Get keyboard input
    QSet<int> pressedKeys;

};


class Bullet:public Sprite{
public:
    Bullet(const QString &imgName, const qreal ang, const QPointF pos, bool owner);
    bool owner; // False represents enemy, true represents player.
};

#endif // SPRITE_H
