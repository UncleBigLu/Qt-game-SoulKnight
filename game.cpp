#include "game.h"
#include "player.h"
#include "statusbar.h"
#include "room.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QPointF>
#include <QTimer>

Game::Game()
{
    // Set view attributes
    setRenderHint(QPainter::Antialiasing);
    resize(1080, 720);
    setBackgroundBrush(QPixmap(":images/map/floor.png"));

    // Set up the scene
    scene = new QGraphicsScene();
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    this->setScene(scene);

    // Initial media player
    playlist[START_MENU] = nullptr;

    playlist[FOREST_THEME] = new QMediaPlaylist();
    playlist[FOREST_THEME]->addMedia(QUrl("qrc:/data/audio/bgSound1.mp3"));
    playlist[FOREST_THEME]->setPlaybackMode(QMediaPlaylist::Loop);

    playlist[BOSS_THEME_1] = nullptr;
    playlist[BOSS_THEME_2] = nullptr;

    bgmPlayer = new QMediaPlayer();
}

Game::~Game()
{
    delete(scene);
    for(int i = 0; i < MUSIC_NUM; ++i)
    {
        delete(playlist[i]);
    }
    delete(bgmPlayer);
    for(int i = 0, n = roomVector.length(); i < n; ++i)
        delete (roomVector[i]);
}



void Game::initialGame(const QString &mapFile)
{
    // Clean up the old scene
    if(scene != nullptr)
        delete(scene);
    // Set up the scene
    scene = new QGraphicsScene();
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    this->setScene(scene);

    //Initial player
    Player *player = new Player(":/images/hero.png");
    scene->addItem(player);

    // Initial statusBar
    StatusBar *bar = new StatusBar();
    scene->addItem(bar);
    bar->setPos(100, 100);
    player->bar = bar;
    bar->maxHP = player->maxHP;
    bar->currentHP = player->currentHP;

    // Initial map
    int mapRowNum = 0;
    QByteArray mapArray[100];
    mapRowNum = readMapFile(mapFile,mapArray);
    initialMap(mapArray,mapRowNum, *scene, player, roomVector);

    // Initial view
    player->parentView = this;
    this->show();

    // Initial timer
    if(timer == nullptr)
        delete(timer);
    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer->start(1000/64);   // 64 frame per second

    // Play bgm;
    bgmPlayer->setPlaylist(playlist[FOREST_THEME]);
    bgmPlayer->setVolume(40);
    bgmPlayer->play();
}

void Game::gameover()
{
    qDebug() << "Gameover fUnc called";
    bgmPlayer->stop();
    timer->stop();
//    // Clear all propeties belong to previous game
//    QList<QGraphicsItem*> itemList = scene->items();
//    for(int i = 0, n = itemList.length(); i < n; ++i)
//        delete (itemList[i]);
//    for(int i = 0, n = roomVector.length(); i < n; ++i)
//        delete (roomVector[i]);

//    qDebug()<< "scene cleared";
    // Show Gameover panel
    QGraphicsPixmapItem *gameOverPanel = new QGraphicsPixmapItem();
    gameOverPanel->setPixmap(QPixmap(":/images/img/gameOver.png"));
    gameOverPanel->setScale(0.8);
    gameOverPanel->setPos(this->mapToScene(0, 0));
    scene->addItem(gameOverPanel);

//    QPushButton* resetButton = new QPushButton();
//    resetButton->setText("Return to start menu");
//    resetButton->resize(200, 100);
//    //connect(resetButton, &QPushButton::clicked, scene, QGraphicsScene)
//    scene->addWidget(resetButton);
//    resetButton->move(this->mapToScene(0, 0).x(),this->mapToScene(0,0).y());
//    connect(resetButton, &QPushButton::clicked, this, &Game::restartGame);

}

void Game::restartGame()
{
    // Clean up the old scene
    delete (scene);

    scene = nullptr;
    // Clean up the timer
    delete (timer);
    timer = nullptr;
    qDebug()<< "scene Released";
    this->initialGame(":/data/map.txt");
    qDebug()<< "Button pressed";
}
