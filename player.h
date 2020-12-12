#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"

class Player:public Sprite{
public:
    // Get keyboard input
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    explicit Player();

    // A reference of view
    QGraphicsView *parentView = nullptr;

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

};



#endif // PLAYER_H
