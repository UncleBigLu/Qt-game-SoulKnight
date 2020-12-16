#ifndef BULLETPOOL_H
#define BULLETPOOL_H
#include <QList>

class Bullet;

class BulletPool
{
public:
    BulletPool(const QString &imgName, bool owner, qreal maxVel = 20, int maxBounceTime = 0);
    ~BulletPool();
    bool owner; // False represents enemy, true represents player.
    int damage = 2;
    int effect = 0;
    int maxBounceTime;

    void pushBullet(Bullet*);
    Bullet* popBullet();

protected:
    uint8_t bulletPoolSize = 30;
    Bullet *pool[30];
    uint8_t bulletPoolIndex = 0;
    QList<Bullet*> removedBullet;
};

#endif // BULLETPOOL_H
