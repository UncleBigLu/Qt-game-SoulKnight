#include "game.h"
#include "player.h"
#include "statusbar.h"
#include "room.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>

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
}



void Game::initialGame(const QString &mapFile)
{
    //Initial player
    Player *player = new Player();
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
    QObject::connect(&timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer.start(1000/64);   // 64 frame per second

    // Play bgm;
    bgmPlayer->setPlaylist(playlist[FOREST_THEME]);
    bgmPlayer->play();
}
