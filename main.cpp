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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // [0]Initial scene
    QGraphicsScene scene;
    // Next line set the scene to a fixed size
    //scene.setSceneRect(0, 0, 1080,720);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
        // Initial player
    Player *player = new Player();
    scene.addItem(player);
        // Initial statusBar
    StatusBar *bar = new StatusBar();
    scene.addItem(bar);
    bar->setPos(100, 100);
    player->bar = bar;
    bar->maxHP = player->maxHP;
    bar->currentHP = player->currentHP;

        // Initial map
    QVector<Room*> roomVector;
    int mapRowNum = 0;
    QByteArray mapArray[100];
    mapRowNum = readMapFile(":/data/map.txt",mapArray);
    initialMap(mapArray, mapRowNum, scene, player, roomVector);

    // [0]Initial scene
    // [1]Initial game view
    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.resize(1080, 720);
    view.setBackgroundBrush(QPixmap(":images/map/floor.png"));
    view.show();
    // Let the player get control of view
    player->parentView = &view;
    // [1]Initial game view

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000/64);   // 64 frame per second

    // Play background music
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/data/audio/bgSound1.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    QMediaPlayer *bgmPlayer = new QMediaPlayer();
    bgmPlayer->setPlaylist(playlist);
    bgmPlayer->play();

    return a.exec();
}
