#ifndef PLAYER_H
#define PLAYER_H

#include <QSet>
#include "sprite.h"

class StatusBar;
class QSoundEffect;

class Player:public Sprite{
public:
    // Get keyboard input
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    explicit Player();
    ~Player();

    // A reference of view
    QGraphicsView *parentView = nullptr;
    // A reference of status bar
    StatusBar *bar = nullptr;
    void getHit(int damage, int effect) override;

private:
    // Max attack speed is 1 bullet per 20 frame
    const unsigned int attackCD = 10;
    unsigned int sinceLastAttack = 0;    // Increase 1 per frame
    // Update frame and position and other properties.
    void advance(int step) override;
    // Get keyboard input
    QSet<int> pressedKeys;
    // Function to change player velocity according to pressedKeys
    void changeVel();
    // Functions to shoot bullets according to pressedKeys and attackCD
    void shoot();
    QSoundEffect *shootSound;
    QSoundEffect *hitSound;

};



#endif // PLAYER_H
