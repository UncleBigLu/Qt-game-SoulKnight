#include "tilemap.h"
#include <QDebug>

TileMap::TileMap(const int type, const QString &imgName, const QPointF pos, int maxFNum, int maxRNum, int fLenth, int fHeight):
    Sprite(imgName, pos, maxFNum, maxRNum, fLenth, fHeight),tileType(type)
{
}

void readMapFile(const QString &fileName, QGraphicsScene& scene)
{
    QFile file(fileName);
    /*
    The QIODevice::Text flag passed to open() tells Qt to
    convert Windows-style line terminators ("\r\n") into C++-style terminators ("\n").
    */
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    int tileX = 0, tileY = 0;
    while (!file.atEnd()){
        QByteArray line = file.readLine();
        tileX = 0;
        for(auto i = line.begin(); i != line.end(); ++i)
        {
            TileMap *m = nullptr;
            if(*i == '#' || *i == '@' || *i == '%')
            {
                m = new TileMap(WALL, ":/images/map/wall.png", QPointF(tileX,tileY), 1, 1,100,100);
            }

            else if(*i == '.')
            {
                m = new TileMap(FLOOR, ":/images/map/floor.png", QPointF(tileX,tileY), 1, 1,100,100);
            }
            else if(*i == 'd')
            {
                m = new TileMap(DOOR, ":/images/map/door.png", QPointF(tileX,tileY-100), 1, 2,100,200);
            }
            else if(*i == ' ')
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
