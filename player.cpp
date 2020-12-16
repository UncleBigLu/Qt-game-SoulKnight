#include "player.h"
#include <QKeyEvent>
#include "bullet.h"
#include "statusbar.h"
#include <QSoundEffect>
#include <QDebug>

// [1]Player class defination------------------------------------------------------
Player::Player(const QString &imgName):
    Sprite(imgName), bulletPool(":/images/bullet0.png", true,20, 2)
{
    // Enable keyboard message receive
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
    // Initial player position at (500, 500)
    this->setPos(500,500);
    // Keep the player at the top of view
    this->setZValue(2);

    maxHP = 80;
    currentHP = maxHP;
    // Initial sound effects--------------------
    shootSound = new QSoundEffect();
    hitSound = new QSoundEffect();
    shootSound->setSource(QUrl("qrc:/data/audio/attack.wav"));

}

Player::~Player()
{
    qDebug() << "player free";
    delete (shootSound);
    delete (hitSound);
}

void Player::getHit(int damage, int effect)
{
    currentHP -= damage;
    if(currentHP < 0)
        currentHP = 0;

    bar->currentHP = this->currentHP;
    bar->update(0, 0, bar->maxLenth, bar->maxWidth);
    if(currentHP <= 0)
        die();
    return;
}
void Player::advance(int step)
{
    if(!step)
    {
        // [0]Get keyboard input
            // Change player velocity according to pressedKeys
        changeVel();
            // Shoot bullets
        shoot();
        // [0]Get keyboard input

    }
    else
    {
        parentView->centerOn(this);
        this->update(0, 0, frameL, frameH);
        //
        bar->setPos(parentView->mapToScene(0, 0));

    }
    move(step);

}

void Player::changeVel()
{
    if(pressedKeys.contains(Qt::Key_W)){
        vel_y = -maxSpeed;
    }
    if(pressedKeys.contains(Qt::Key_S)){
        vel_y = maxSpeed;
    }
    if(pressedKeys.contains(Qt::Key_A)){
        vel_x = -maxSpeed;
        // Let the player face to left
        currentRow = 0;
    }
    if(pressedKeys.contains(Qt::Key_D)){
        vel_x = maxSpeed;
        // Let the player face to right
        currentRow = 1;
    }
}

void Player::shoot()
{
    if(sinceLastAttack < attackCD){
        ++sinceLastAttack;
        return;
    }

    // Shoot bullets
    // Play sound effect
    shootSound->play();

    qreal tmp_angel = 0;
    int shootBtnNum = 0;
    if(pressedKeys.contains(Qt::Key_J)){
        tmp_angel +=180;
        shootBtnNum ++;
    }
    if(pressedKeys.contains(Qt::Key_I)){
        tmp_angel += 90;
        shootBtnNum++;
    }
    if(pressedKeys.contains(Qt::Key_K)){
        tmp_angel += 270;
        shootBtnNum++;
    }
    if(pressedKeys.contains(Qt::Key_L)){
        tmp_angel += 360;
        shootBtnNum++;
    }
    if(shootBtnNum > 0){
        sinceLastAttack = 0;
        // Generate bullets
        tmp_angel = tmp_angel / shootBtnNum;
        // Turn the angel into radians

        // FORCE BUG FIX------------------------------------
        if(pressedKeys.contains(Qt::Key_L)&&pressedKeys.contains(Qt::Key_I))
        {
            tmp_angel = 45;
        }
        // END OF FORCE BUG FIX-----------------------------

        tmp_angel = tmp_angel / 180 * 3.142;

        // Add bullet to the scene-------------------------------------
//        bulletPoor[bulletPoorIndex]->angle = tmp_angel;
//        bulletPoor[bulletPoorIndex]->vel_x = bulletPoor[bulletPoorIndex]->maxSpeed * qCos(tmp_angel);
//        bulletPoor[bulletPoorIndex]->vel_y = -(bulletPoor[bulletPoorIndex]->maxSpeed * qSin(tmp_angel));
//        bulletPoor[bulletPoorIndex]->setPos(this->pos());
//        this->scene()->addItem(bulletPoor[bulletPoorIndex]);
//        bulletPoorIndex = (bulletPoorIndex + 1) % bulletPoorSize;
        Bullet* b = bulletPool.popBullet();
        b->angle = tmp_angel;
        b->vel_x = b->maxSpeed * qCos(tmp_angel);
        b->vel_y = -(b->maxSpeed * qSin(tmp_angel));
        b->setPos(this->pos());
        this->scene()->addItem(b);
        // End of shoot bullets--------------------------------------
    }

}




void Player::keyPressEvent(QKeyEvent *event){
    pressedKeys += event->key();
}

void Player::keyReleaseEvent(QKeyEvent *event){
    vel_x = 0; vel_y = 0;
    pressedKeys -= event->key();

}
