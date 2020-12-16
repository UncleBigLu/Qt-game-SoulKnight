#include "room.h"
#include <QFile>
#include "tilemap.h"
#include "enemy.h"
#include "player.h"
#include <QDebug>

Room::Room(QPointF topLeft):
    topLeft(topLeft)
{

}

Room::~Room()
{
    for(int i = 0, n = spriteList.length(); i < n; ++i)
        delete (spriteList[i]);
}

int readMapFile(const QString &fileName, QByteArray a[])
{
    QFile file(fileName);
    /*
    The QIODevice::Text flag passed to open() tells Qt to
    convert Windows-style line terminators ("\r\n") into C++-style terminators ("\n").
    */
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;
    int arrayLen = 0;
    while (!file.atEnd())
    {
        a[arrayLen++] = file.readLine();
    }
    return arrayLen;
}

void initialMap(QByteArray a[],int arrayLenth, QGraphicsScene &scene, Player *player, QVector<Room*> &roomList)
{
    int tileX = 0, tileY = 0;
    for(int counter = 0; counter < arrayLenth; ++counter)
    {
        tileX = 0;
        for(int i = 0, n = a[counter].length(); i != n; ++i)
        {
            TileMap *m = nullptr;
            if(a[counter][i] == '@')   // Top left of a room.
            {
                // Store room top left and width, height message
                Room *room = new Room(QPointF(tileX, tileY));
                int tmp_w = 1, tmp_h = 1;
                while(a[counter][i+tmp_w] != '%')
                    ++tmp_w;
                while (a[counter+tmp_h][i] != '%')
                    ++tmp_h;
                room->width = tmp_w + 1;
                room->height = tmp_h + 1;
                int tmp_tileX = tileX, tmp_tileY = tileY;
                // Initial monster and door that belongs to this room
                for(int j = 0; j < room->height; ++j)
                {
                    tmp_tileX = tileX;
                    for(int k = 0; k < room->width; ++k)
                    {
                        if(a[counter+j][i+k] == 'e')
                        {
                            Enemy* enemy = new Enemy(":images/monster0.png", QPointF(tmp_tileX, tmp_tileY), player, room);
                            scene.addItem(enemy);
                            room->enemyNum++;
                            room->spriteList.append(enemy);
                            tmp_tileX += 100;
                        }
                        else if(a[counter+j][i+k] == 'D')
                        {
                           TileMap* d = new TileMap(DOOR, ":/images/map/door.png", QPointF(tmp_tileX,tmp_tileY-100), false, 1, 2,100,200);
                           d->setZValue(1);
                           scene.addItem(d);
                           room->spriteList.append(d);
                           tmp_tileX += 100;
                        }
                        else if(a[counter+j][i+k] == 'T')
                        {
                            TriggerTile* t = new TriggerTile(FLOOR, ":/images/map/floor.png",QPointF(tmp_tileX, tmp_tileY), room);
                            scene.addItem(t);
                            tmp_tileX += 100;
                        }
                        else {
                            tmp_tileX += 100;
                        }
                    }
                    tmp_tileY += 100;
                }
                roomList.append(room);

                m = new TileMap(WALL, ":/images/map/wall.png", QPointF(tileX,tileY), true);
            }
            else if (a[counter][i] == 'p')
            {
                player->setPos(tileX, tileY);
                tileX += 100;
                continue;
            }

            else if(a[counter][i] == '#' || a[counter][i] == '%')
            {
                m = new TileMap(WALL, ":/images/map/wall.png", QPointF(tileX,tileY), true);
            }
            else
            {
                tileX += 100;
                continue;
            }

            if(m != nullptr)
            {
                scene.addItem(m);
                tileX += 100;
            }
        }
        tileY += 100;

    }
}

void Room::startBattle()
{
    if(enemyNum <= 0)
       return;
    for(int i = 0, n = spriteList.length(); i < n; ++i)
    {
        if(typeid (*(spriteList[i])) == typeid (Enemy))
        {
            // Wake up the enemy
            Enemy *tmpPoint = dynamic_cast<Enemy*>(spriteList[i]);
            tmpPoint->isAwake = true;
        }
        else if(typeid (*(spriteList[i])) == typeid (TileMap))
        {
            // Close the door
            TileMap *tmpPoint = dynamic_cast<TileMap*>(spriteList[i]);
            tmpPoint->isCollidBlock = true;
            tmpPoint-> currentRow = 1;
            tmpPoint->update(0,0,100, 200);
        }

    }
}

void Room::endBattle()
{
    qDebug() << spriteList.length();
    if(enemyNum > 0)
        return;
    // Open the door
    for(int i = 0, n = spriteList.length(); i < n; ++i)
    {
        if(typeid (*(spriteList[i])) == typeid (TileMap))
        {
            TileMap *tmpPoint = dynamic_cast<TileMap*>(spriteList[i]);
            tmpPoint->isCollidBlock = false;
            tmpPoint-> currentRow = 0;
            tmpPoint->update(0,0,100, 200);
        }
    }
}
