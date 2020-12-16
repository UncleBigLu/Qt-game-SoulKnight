#include "bulletpool.h"
#include "bullet.h"

BulletPool::BulletPool(const QString &imgName, bool owner, qreal maxVel, int maxBounceTime)
{
    bulletPoolSize = 30;
    for(int i = 0; i < bulletPoolSize; ++i)
    {
        pool[i] = new Bullet(imgName,owner,this, maxVel, maxBounceTime);
        removedBullet.append(pool[i]);
    }
}

BulletPool::~BulletPool()
{
    for(int i = 0, n = removedBullet.length(); i < n; ++i)
    {
        delete (removedBullet[i]);
    }
}

Bullet* BulletPool::popBullet()
{
    removedBullet.removeOne(pool[bulletPoolIndex]);
    Bullet* ret = pool[bulletPoolIndex];
    bulletPoolIndex = (bulletPoolIndex+1) % bulletPoolSize;
    return ret;
}

void BulletPool::pushBullet(Bullet *b)
{
    removedBullet.append(b);
}
