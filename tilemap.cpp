#include "tilemap.h"
#include <QDebug>
#include "sprite.h"

TileMap::TileMap(const int type, const QString &imgName, const QPointF pos, bool isCollid, int maxFNum, int maxRNum, int fLenth, int fHeight):
    Sprite(imgName, pos, maxFNum, maxRNum, fLenth, fHeight),tileType(type), isCollidBlock(isCollid)
{
}

void TileMap::getHit(int damage, int effect)
{
    return;
}

QPointF readMapFile(const QString &fileName, QGraphicsScene& scene, Player* p)
{

    QPointF playerPos(0, 0);
    QFile file(fileName);
    /*
    The QIODevice::Text flag passed to open() tells Qt to
    convert Windows-style line terminators ("\r\n") into C++-style terminators ("\n").
    */
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QPointF(0, 0);
    int tileX = 0, tileY = 0;
    while (!file.atEnd()){
        QByteArray line = file.readLine();
        tileX = 0;
        for(auto i = line.begin(); i != line.end(); ++i)
        {
            TileMap *m = nullptr;
            if(*i == '#' || *i == '@' || *i == '%')
            {
                m = new TileMap(WALL, ":/images/map/wall.png", QPointF(tileX,tileY), true);
            }
            else if(*i == 't')
            {
                Enemy* enemy = new Enemy(":images/monster0.png", QPointF(tileX, tileY), p);
                scene.addItem(enemy);
                tileX += 100;
            }
            else if(*i == '.')
            {   // Floor, do nothing, as the view background has filled the floor.
                tileX += 100;
                continue;
            }
            else if(*i == 'D')
            {
                m = new TileMap(DOOR, ":/images/map/door.png", QPointF(tileX,tileY-100), false, 1, 2,100,200);
            }
            else if (*i == 'p') {
                playerPos.setX(tileX); playerPos.setY(tileY);
                tileX += 100;
                continue;
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

    return playerPos;
}
