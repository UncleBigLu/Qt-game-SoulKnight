#ifndef TILEMAP_H
#define TILEMAP_H

#include "sprite.h"
#include <QFile>
#include "player.h"
#include "enemy.h"

enum {FLOOR=0, WALL, DOOR, BOX};

QPointF readMapFile(const QString &fileName, QGraphicsScene&, Player*);


class TileMap : public Sprite
{
public:
    TileMap(const int type, const QString &imgName, const QPointF pos,
            bool isCollid = false, int maxFNum = 1, int maxRNum = 1, int fLenth = 100, int fHeight = 100);
    const int tileType;
    bool isCollidBlock;
    void getHit(int damage, int effect) override;
};

#endif // TILEMAP_H
