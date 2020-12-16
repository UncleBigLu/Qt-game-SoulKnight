#ifndef ENEMY_H
#define ENEMY_H


#include "sprite.h"
#include "bullet.h"
#include "bulletpool.h"

class Player;
class Room;
class Bullet;

class Enemy:public Sprite{
public:
    Enemy(const QString &imgName, const QPointF pos, Player* atkTarget, Room *parentRoom,
          int maxHP = 10, int maxFNum = 4, int maxRNum = 2, int fLenth = 100, int fHeight = 100);
    Player *attackTarget = nullptr;
    Room *parentRoom;
    void die() override;
    bool isAwake = false;
    ~Enemy();
private:
    // Attack attributes----------------------------------------
    // Time interval between two bullets
    const unsigned int shootCD = 20;
    unsigned int sinceLastShoot = 0;
    // Time interval between two attacks
    const unsigned int attackCD = 300;
    unsigned int sinceLastAttack = 0;
    // Bullet num per attack
    const unsigned int bulletCapacity = 3;
    unsigned int currentBulletNum = bulletCapacity;
    // End of attack attributes===================================
    // Movement attributes-------------------------------------
    const unsigned int moveCD = 150;
    unsigned int sinceLastMove = 0;
    const unsigned int maxMoveTime = 320;
    unsigned int moveKeepTime = 0;
    bool canMove = false;

    // End of movement attributes===================================
    // Enemy's bullet pool---------------------------------
    BulletPool bulletPool;

    void shoot();
    void changeDirToPlayer();
    void advance(int step) override;
    void move(int step) override;



};

#endif // ENEMY_H
