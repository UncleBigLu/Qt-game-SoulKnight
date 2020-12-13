#include "sprite.h"

#include <QDebug>
#include <QtMath>
#include "tilemap.h"
#include <QRandomGenerator>
// [0]Sprite class defination
Sprite::Sprite()
{
    spriteImage = new QPixmap(":/images/hero.png");

}

Sprite::Sprite(const QString &imgName)
{
    spriteImage = new QPixmap(imgName);
}

Sprite::Sprite(const QString &imgName, const QPointF pos, int maxFNum, int maxRNum, int fLenth, int fHeight):
    maxFrameNum(maxFNum), maxRowNum(maxRNum), frameL(fLenth), frameH(fHeight)
{
    spriteImage = new QPixmap(imgName);
    nextPos = pos;
    setPos(pos);
}

QRectF Sprite::boundingRect() const{
    qreal adjust = 1;
    return QRectF(0 + adjust, 0 + adjust,
                  frameL - adjust, frameH - adjust);
}

QPainterPath Sprite::shape() const{
    QPainterPath path;
    qreal adjust = 10;
    path.addRect(0+ adjust, 0 + adjust,
                 frameL - adjust, frameH - adjust);
    return path;
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

bool Sprite::isMoving() const
{
    return (vel_x != 0 || vel_y != 0);
}

void Sprite::getHit(int damage, int effect)
{
    currentHP -= damage;
    if(currentHP <= 0)
        die();
    return;
}

void Sprite::die()
{
    scene()->removeItem(this);

    delete (this);
    return;
}



void Sprite::advance(int step)
{
    if(!step)
    {
        // [0]Prepare to move the Item

        if(!isMoving())
            return;
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
    if(sinceLastFrame < frameUpdateCD)
    {
        ++sinceLastFrame;
        return;
    }
    sinceLastFrame = 0;
    currentFrame += 1;
    if(currentFrame >=maxFrameNum) currentFrame = 0;
    this->update(0,0,frameL,frameH);
}

void Sprite::move(int step)
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
        if(!collidV)
            nextPos.setY(y()+vel_y);
        setPos(nextPos);

        nextFrame();
        // [0]Prepare to move the Item END
        return;
    }
}
// [0]Sprite class defination

bool wallCollidCheck(const Sprite *s)
{
    QList<QGraphicsItem *> colliding_items = s->collidingItems();
    // Collid exam with the wall
    for(int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if(typeid (*(colliding_items[i])) == typeid (TileMap))
        {
            TileMap *tmpPoint = dynamic_cast<TileMap*>(colliding_items[i]);
            if(tmpPoint->isCollidBlock)
            {
                // Move will cause collidsion
                return true;
            }
        }
    }
    return false;
}

