#include "enemy.h"

void Enemy::advance(int step)
{
    if(!step){ // Prepare to take action
        // Update animation
        nextFrame();
        // Shoot bullets
        shoot();
        // Move
        if(canMove)
        {
            move(step);
            moveKeepTime++;

        }
        if(!canMove && sinceLastMove < moveCD)
        {
            ++sinceLastMove;
        }
        if(sinceLastMove >= moveCD)
        {
            canMove = true;
            changeDirToPlayer();
            sinceLastMove = 0;
        }
        if(moveKeepTime >= maxMoveTime && canMove)
        {
            moveKeepTime = 0;
            canMove = false;
        }

    }
}

Enemy::Enemy(const QString &imgName, const QPointF pos, Player* atkTarget,
             int maxHP, int maxFNum, int maxRNum, int fLenth, int fHeight):
    Sprite(imgName, pos, maxFNum, maxRNum, fLenth, fHeight), maxHP(maxHP)
{
    attackTarget = atkTarget;
    // Keep the enemy at the top of map
    this->setZValue(1);
}

void Enemy::shoot(){
    if(sinceLastAttack < attackCD)
    {
        ++sinceLastAttack;
        return;
    }
    if(currentBulletNum <= 0)
    {
        sinceLastAttack = 0;
        currentBulletNum = bulletCapacity;
        return;
    }
    if(sinceLastShoot < shootCD)
    {
        ++sinceLastShoot;
        return;
    }
    QLineF atkLine(pos(), attackTarget->pos());
    qreal ang = atkLine.angle() + (QRandomGenerator::global()->bounded(10) - QRandomGenerator::global()->bounded(10));
    Bullet *bullet = new Bullet(":/images/bullet1.png",ang/180*3.142,pos(),false, 10);
    scene()->addItem(bullet);
    --currentBulletNum;
    sinceLastShoot = 0;

}

void Enemy::changeDirToPlayer()
{
    QLineF *atkLine = new QLineF(this->pos(), attackTarget->pos());
    angle = atkLine->angle();
    vel_x = cos(angle/180*3.142) * maxSpeed;
    vel_y = -sin(angle/180*3.142) * maxSpeed;
    delete (atkLine);
}



void Enemy::move(int step)
{
    if(!isMoving())
        return;
    bool collidH, collidV;
    if(!step)
    {
        prevPos = this->pos();
        nextPos.setX(x()+vel_x);
        setPos(nextPos);
        collidH = wallCollidCheck(this);
        setPos(prevPos);

        nextPos = prevPos;
        nextPos.setY(y()+vel_y);
        setPos(nextPos);
        collidV = wallCollidCheck(this);
        setPos(prevPos);

        nextPos = prevPos;
        if(!collidH)
            nextPos.setX(x()+vel_x);
        else
            vel_x = -vel_x;     // Bounce
        if(!collidV)
            nextPos.setY(y()+vel_y);
        else {
            vel_y = -vel_y;     // Bounce
        }
        setPos(nextPos);
        if(vel_x >= 0)
            currentRow = 1;     // Let the enemy face to right
        else
            currentRow = 0;

        // [0]Prepare to move the Item END
        return;
    }
}