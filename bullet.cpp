#include "bullet.h"
#include <QtMath>
#include "tilemap.h"
#include "enemy.h"
#include "player.h"
#include <QDebug>
Bullet::Bullet(const QString &imgName, const qreal ang, const QPointF pos, bool own, BulletPool* parentPool,
               qreal maxVel, int maxBounceTime):
    owner(own), maxBounceTime(maxBounceTime),bounceCounter(maxBounceTime), parentPool(parentPool)
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

Bullet::Bullet(const QString &imgName, bool owner,BulletPool* parentPool,
               qreal maxVel, int maxBounceTime):
    owner(owner), maxBounceTime(maxBounceTime),bounceCounter(maxBounceTime), parentPool(parentPool)
{
    // Initial source picture
        spriteImage = new QPixmap(imgName);
        // Initial other properties
        maxSpeed = maxVel;
        maxFrameNum = 1;
        maxRowNum = 1;
        frameH = 40;
        frameL = 40;
}

Bullet::~Bullet()
{

}

void Bullet::advance(int step)
{
    if(!step)
    {// Prepare to move
        nextFrame();
        bool collidH = false, collidV = false;
        prevPos = this->pos();
        nextPos.setX(x()+vel_x);
        setPos(nextPos);
        QList<QGraphicsItem *> colliding_items = this->collidingItems();
        for(int i = 0, n = colliding_items.size(); i < n; ++i)
        {
            if(typeid (*(colliding_items[i])) == typeid (TileMap))
            {
                TileMap *tmpPoint = dynamic_cast<TileMap*>(colliding_items[i]);
                if(tmpPoint->isCollidBlock)
                {
                    // Move will cause collidsion
                    collidH = true;
                }
                if(tmpPoint->tileType == BOX)
                {
                    tmpPoint->getHit(damage, effect);
                }
            }
            else if((typeid (*(colliding_items[i])) == typeid (Enemy) && owner == true)
                    || (typeid (*(colliding_items[i])) == typeid (Player) && owner == false))
            {
                Sprite *tmpPoint = dynamic_cast<Sprite*>(colliding_items[i]);
                tmpPoint->getHit(damage, effect);
                scene()->removeItem(this);
                this->parentPool->pushBullet(this);
                return;
            }
        }
        setPos(prevPos);

        nextPos = prevPos;
        nextPos.setY(y()+vel_y);
        setPos(nextPos);
        QList<QGraphicsItem *> colliding_items2 = this->collidingItems();
        for(int i = 0, n = colliding_items2.size(); i < n; ++i)
        {
            if(typeid (*(colliding_items2[i])) == typeid (TileMap))
            {
                TileMap *tmpPoint = dynamic_cast<TileMap*>(colliding_items2[i]);
                if(tmpPoint->isCollidBlock)
                {
                    // Move will cause collidsion
                    collidV = true;
                }
                if(tmpPoint->tileType == BOX)
                {
                    tmpPoint->getHit(damage, effect);
                }
            }
            else if((typeid (*(colliding_items2[i])) == typeid (Enemy) && owner == true)
                    || (typeid (*(colliding_items2[i])) == typeid (Player) && owner == false))
            {
                Sprite *tmpPoint = dynamic_cast<Sprite*>(colliding_items2[i]);
                tmpPoint->getHit(damage, effect);
                scene()->removeItem(this);
                this->parentPool->pushBullet(this);
                return;
            }
        }
        setPos(prevPos);

        nextPos = prevPos;
        if(!collidH)
            nextPos.setX(x()+vel_x);
        else if(bounceCounter > 0)
        {
            vel_x = -vel_x;     // Bounce
            bounceCounter--;
        }
        else
        {
            bounceCounter = maxBounceTime;
            scene()->removeItem(this);
            this->parentPool->pushBullet(this);
            return;
        }

        if(!collidV)
            nextPos.setY(y()+vel_y);
        else if(bounceCounter > 0){
            bounceCounter--;
            vel_y = -vel_y;     // Bounce
        }
        else {
            bounceCounter = maxBounceTime;
            scene()->removeItem(this);
            this->parentPool->pushBullet(this);
            return;
        }
        setPos(nextPos);


        // [0]Prepare to move the Item END
        return;
    }
}
