#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "sprite.h"
#include "tilemap.h"

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
        // Initial map
    readMapFile(":/data/map.txt",scene);
    // [0]Initial scene
    // [1]Initial game view
    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.resize(1080, 720);
    view.centerOn(player);
    view.show();
    // Let the player get control of view
    player->parentView = &view;
    // [1]Initial game view

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(1000/64);   // 64 frame per second




    return a.exec();
}
