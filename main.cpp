

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "sprite.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene scene;
    // Set the scene to a fixed size
    //scene.setSceneRect(0, 0, 1080,720);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    Player *player = new Player();
    scene.addItem(player);

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.resize(1080, 720);
    view.centerOn(player);
    view.show();
    // Let the player get control of view
    player->parentView = &view;


    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &scene, &QGraphicsScene::advance);
    timer.start(500/33);




    return a.exec();
}
