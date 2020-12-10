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
    Sprite(const QString &imgName);
    Sprite(const QString &imgName, const QPointF pos, int maxFNum, int maxRNum, int fLenth, int fHeight);
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
    // Max attack speed is 1 bullet per 20 frame
    const int attackCD = 10;
    int sinceLastAttack = 0;    // Increase 1 per frame
    // Update frame and position and other properties.
    void advance(int step) override;
    // Get keyboard input
    QSet<int> pressedKeys;
    // Function to change player velocity according to pressedKeys
    void changeVel();
    // Functions to shoot bullets according to pressedKeys and attackCD
    void shoot();
};


class Bullet:public Sprite{
public:
    Bullet(const QString &imgName, const qreal ang, const QPointF pos, bool owner);
    bool owner; // False represents enemy, true represents player.
    int damage = 2;
};

#endif // SPRITE_H
