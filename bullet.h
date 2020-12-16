#ifndef BULLET_H
#define BULLET_H

#include "sprite.h"
class BulletPool;

class Bullet:public Sprite{
public:
    Bullet(const QString &imgName, const qreal ang, const QPointF pos, bool owner,BulletPool* parentPool, qreal maxVel = 20, int maxBounceTime = 0);
    Bullet(const QString &imgName, bool owner, BulletPool* parentPool, qreal maxVel = 20, int maxBounceTime = 0);
    ~Bullet();
    bool owner; // False represents enemy, true represents player.
    int damage = 2;
    int effect = 0;
    void advance(int step) override;
    int maxBounceTime;
    int bounceCounter;
private:
    BulletPool* parentPool;

};


#endif // BULLET_H
