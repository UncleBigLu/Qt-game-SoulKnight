#include "sprite.h"
#include <QKeyEvent>
#include <QDebug>
#include <QtMath>

//Sprite::Sprite(QObject *parent) :
//    QObject(parent), QGraphicsItem()
//{
//    currentFrame = 0;   // Sets the coordinates of the current frame of the sprite
//    spriteImage = new QPixmap(":images/hero.png"); // Load the sprite image QPixmap

//    timer = new QTimer();   // Create a timer for sprite animation
//    connect(timer, &QTimer::timeout, this, &Sprite::nextFrame);
//    timer->start(25);   // Run the sprite on the signal generation with a frequency of 25 ms
//}
// [0]Sprite class defination
Sprite::Sprite()
{
    spriteImage = new QPixmap(":/images/hero.png");

}

QRectF Sprite::boundingRect() const{
    qreal adjust = 1;
    return QRectF(0 - adjust, 0 - adjust,
                  frameL + adjust, frameH + adjust);
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    /* In the graphic renderer we draw the sprite
     * The first two arguments - is the X and Y coordinates of where to put QPixmap
     * The third argument - a pointer to QPixmap
     * 4 and 5 of the arguments - The coordinates in the image QPixmap, where the image is displayed
     * By settqDebug()<<(event->key());ing the X coordinate with the variable currentFrame we would like to move the camera on the sprite
     * and the last two arguments - the width and height of the displayed area, that is, the frame
     * */
    painter->drawPixmap(0, 0, *spriteImage, currentFrame*frameL, currentRow*frameH, frameL, frameH);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

bool Sprite::isMoving()
{
    return (vel_x != 0 || vel_y != 0);
}// Initial source picture


void Sprite::advance(int step)
{
    if(!step)
    {
        // [0]Prepare to move the Item
        nextPos.setX(x()+vel_x);
        nextPos.setY(y()+vel_y);
        // [0]Prepare to move the Item END
        return;
    }

    if(isMoving())
    {
        // Animation
        nextFrame();
        // Move the item position

        setPos(nextPos);
    }
}

void Sprite::nextFrame(){
    currentFrame += 1;
    if(currentFrame >=maxFrameNum) currentFrame = 0;
    this->update(0,0,frameL,frameH);
}
// [0]Sprite class defination
// [1]Player class defination
Player::Player(){
    // Enable keyboard message receive
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
    // Initial player position at (500, 500)
    this->setPos(500,500);
}
void Player::advance(int step)
{
    if(!step)
    {
        // [0]Get keyboard input
        // Move up
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
            // Shoot bullets
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

            Bullet *b = new Bullet(":/images/bullet0.png",tmp_angel,this->pos(),true);

            this->scene()->addItem(b);
            b->setPos(x(), y());
        }
        // [0]Get keyboard input
    }

    if(isMoving())
    {
        // Center the view
        parentView->centerOn(this);
    }
    // Call the parent function to play animation and move the player
    Sprite::advance(step);
}

void Player::keyPressEvent(QKeyEvent *event){
    pressedKeys += event->key();
}

void Player::keyReleaseEvent(QKeyEvent *event){
    vel_x = 0; vel_y = 0;
    pressedKeys -= event->key();

}

Bullet::Bullet(const QString &imgName, const qreal ang, const QPointF pos, bool own):
    owner(own)
{
    // Initial source picture
        spriteImage = new QPixmap(imgName);
        // Initial other properties
        maxSpeed = 20;
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
