#ifndef ROOM_H
#define ROOM_H

#include <QList>
#include <QPointF>
#include <QVector>
class Enemy;
class Tilemap;
class Player;
class QGraphicsScene;
class Sprite;

class Room
{
public:
    Room(QPointF topLeft);
    ~Room();
    // Contains every sprites belongs to this room(including enemy and door in this version of code)
    QList<Sprite*> spriteList;
    QList<Sprite*> removedSprites;
    QPointF topLeft;
    int width;  //     @##%
    int height; // Eg: %##%, width = 4, height = 2
    int enemyNum = 0;
    void startBattle();
    void endBattle();
};

int readMapFile(const QString &fileName, QByteArray a[]);
void initialMap(QByteArray a[],int arrayLenth, QGraphicsScene&, Player*, QVector<Room*>&);

#endif // ROOM_H
