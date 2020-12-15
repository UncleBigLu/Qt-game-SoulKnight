#include "tilemap.h"
#include <QDebug>
#include "sprite.h"
#include <QFile>
#include "enemy.h"
#include "player.h"
#include "room.h"

TileMap::TileMap(const int type, const QString &imgName, const QPointF pos, bool isCollid, int maxFNum, int maxRNum, int fLenth, int fHeight):
    Sprite(imgName, pos, maxFNum, maxRNum, fLenth, fHeight),tileType(type), isCollidBlock(isCollid)
{
}

void TileMap::getHit(int damage, int effect)
{
    return;
}


TriggerTile::TriggerTile(const int type, const QString &imgName, const QPointF pos, Room *parentRoom,
                         bool isCollid, int maxFNum, int maxRNum, int fLenth, int fHeight):
    TileMap(type, imgName, pos, isCollid,maxFNum,maxRNum,fLenth, fHeight), parentRoom(parentRoom)
{

}

void TriggerTile::advance(int step)
{
    if(!step)
    {
        QList<QGraphicsItem *> colliding_items = this->collidingItems();
        // Collid exam with the wall
        for(int i = 0, n = colliding_items.size(); i < n; ++i)
        {
            if(typeid (*(colliding_items[i])) == typeid (Player))
            {
                parentRoom->startBattle();
            }
        }
    }

}
