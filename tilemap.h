#ifndef TILEMAP_H
#define TILEMAP_H

#include "sprite.h"
#include <QFile>

enum {FLOOR=0, WALL, DOOR, BOX};

void readMapFile(const QString &fileName, QGraphicsScene&);


class TileMap : public Sprite
{
public:
    TileMap(const int type, const QString &imgName, const QPointF pos, int maxFNum, int maxRNum, int fLenth, int fHeight);
    const int tileType;
};

#endif // TILEMAP_H
