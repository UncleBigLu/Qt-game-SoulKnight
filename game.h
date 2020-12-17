#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QVector>

class QGraphicsScene;
class QMediaPlaylist;
class QMediaPlayer;
class Room;
class QTimer;

enum Music{
    START_MENU = 0, FOREST_THEME, BOSS_THEME_1, BOSS_THEME_2
};
#define MUSIC_NUM 4

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game();
    ~Game();
    // Public methods
    void displayMainMenu();
    void initialGame(const QString &mapFile);
    void gameover();
    void changeMusic(int music);
    // Public attributes
    QGraphicsScene* scene;
public slots:
    void restartGame();

private:
    QTimer* timer = nullptr;
    QMediaPlaylist *playlist[MUSIC_NUM];
    QMediaPlayer *bgmPlayer;
    QVector<Room*> roomVector;
};

#endif // GAME_H
