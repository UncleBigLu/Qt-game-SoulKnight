#ifndef BULLET_H
#define BULLET_H

#include "sprite.h"
#include "tilemap.h"
#include "player.h"
#include "enemy.h"

class Bullet:public Sprite{
public:
    Bullet(const QString &imgName, const qreal ang, const QPointF pos, bool owner, qreal maxVel = 20, int maxBounceTime = 0);
    bool owner; // False represents enemy, true represents player.
    int damage = 2;
    int effect = 0;
    void advance(int step) override;
private:
    int maxBounceTime;

};


#endif // BULLET_H
