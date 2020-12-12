# Qt Soul Knight

Try to imitate soul knight game using qt.

## Code structure

###  Images:
All images locates at img folder.
hero.png: total size 400\*200 pixe, each frame size is 100\*100
bullet0&1: 40\*40

## About map.txt
'#' represents wall.

'p': player initial position.

'@' represents the upper left corner of a fight room. It's also initialized as a wall when initializing the map.

'%' represents the other three corner of a fight room.

'e' represents a single enemy.

'E' represents the end of the map or the export. When you arrive here, you win the game or you enter the next level.

'.' represents floor(since the floor don't interact with any object, the floor blocks 
are implemented with view background instead of Sprite. Therefore '.' does nothing 
in the current version of code).

'D' represents the room door.



### Class:

#### Player

Keyboard input was implemented in `Player::advance` function. See also `keyPressEvent()` and `keyReleaseEvent()`.



