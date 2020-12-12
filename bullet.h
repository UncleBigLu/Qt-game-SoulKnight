#ifndef BULLET_H
#define BULLET_H

#include "sprite.h"

class Bullet:public Sprite{
public:
    Bullet(const QString &imgName, const qreal ang, const QPointF pos, bool owner, qreal maxVel = 20);
    bool owner; // False represents enemy, true represents player.
    int damage = 2;
};


#endif // BULLET_H
