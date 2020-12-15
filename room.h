#ifndef ROOM_H
#define ROOM_H

#include <QList>
#include <QPointF>
#include <QVector>
class Enemy;
class Tilemap;
class Player;
class QGraphicsScene;

class Room
{
public:
    Room(QPointF topLeft);
    QList<Enemy*> enemyList;

    QPointF topLeft;
    int width;  //     @##%
    int height; // Eg: %##%, width = 4, height = 2
};

int readMapFile(const QString &fileName, QByteArray a[]);
void initialMap(QByteArray a[],int arrayLenth, QGraphicsScene&, Player*, QVector<Room>&);

#endif // ROOM_H
