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

void initialMap(QByteArray a[],int arrayLenth, QGraphicsScene &scene, Player *player, QVector<Room> &roomList)
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
                Room room(QPointF(tileX, tileY));
                int tmp_w = 1, tmp_h = 1;
                while(a[counter][i+tmp_w] != '%')
                    ++tmp_w;
                while (a[counter+tmp_h][i] != '%')
                    ++tmp_h;
                room.width = tmp_w + 1;
                room.height = tmp_h + 1;
                int tmp_tileX = tileX, tmp_tileY = tileY;
                // Initial monster and door that belongs to this room
                for(int j = 0; j < room.height; ++j)
                {
                    tmp_tileX = tileX;
                    for(int k = 0; k < room.width; ++k)
                    {
                        if(a[counter+j][i+k] == 'e')
                        {
                            Enemy* enemy = new Enemy(":images/monster0.png", QPointF(tmp_tileX, tmp_tileY), player);
                            scene.addItem(enemy);
                            room.enemyList.append(enemy);
                            tmp_tileX += 100;
                        }
                        else {
                            tmp_tileX += 100;
                        }
                    }
                    tmp_tileY += 100;
                }
                roomList.append(room);
                qDebug()<<room.topLeft << room.width<< room.height<<room.enemyList.length();

                m = new TileMap(WALL, ":/images/map/wall.png", QPointF(tileX,tileY), true);
            }
            else if(a[counter][i] == 'D')
            {
                 m = new TileMap(DOOR, ":/images/map/door.png", QPointF(tileX,tileY-100), false, 1, 2,100,200);
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
