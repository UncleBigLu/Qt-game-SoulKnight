#include "bullet.h"
#include <QtMath>

Bullet::Bullet(const QString &imgName, const qreal ang, const QPointF pos, bool own, qreal maxVel):
    owner(own)
{
    // Initial source picture
        spriteImage = new QPixmap(imgName);
        // Initial other properties
        maxSpeed = maxVel;
        maxFrameNum = 1;
        maxRowNum = 1;
        frameH = 40;
        frameL = 40;
        angle = ang;
        vel_x = maxSpeed * qCos(angle);
        vel_y = -(maxSpeed * qSin(angle));
        nextPos = pos;
        setPos(pos);
        //setRotation(angel);
}
