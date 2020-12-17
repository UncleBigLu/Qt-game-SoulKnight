#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "sprite.h"
#include "tilemap.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "statusbar.h"
#include "room.h"
#include <QDebug>
#include <QVector>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game game;
    game.initialGame(":/data/map.txt");

    return a.exec();
}
