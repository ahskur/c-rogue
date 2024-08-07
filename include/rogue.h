// if not defined, define and close
#ifndef ROGUE_H
#define ROGUE_H

// typedefs
// statements
// methods

/* As of 04.08.2024 ncurses it's bugged, 
so you need to define this shit and compile with 
gcc main.c -lncurses
*/
#define NCURSES_STATIC
#include <ncurses/ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Position {
    int x;
    int y;
} Position;


typedef struct Player{
    /* Define an "alias" for the struct Player also called Player*/
    Position position;
    int health;
    // Room * room;
} Player;


typedef struct Room {
    Position position;
    int enemies;
    int height;
    int width;
    /* Doors are an array bc can be 4 doors each room*/
    Position ** doors;
    /* Note for for me
    Check what ** are before procceding*/
    //Monster ** monsters;
    //Item ** items;

} Room;

int screenSetup();

/* Level methods */
Room ** mapSetup();
char ** saveLevelPos();


/* Player methods */
/* Here is declaring the method that returns a pointer to the struct Player*/
Player * playerSetup();
int playerMove(int y, int x, Player * user);
int playerInput(int input, Player * user);
int checkPosition(int newY, int newX, Player * user);


/* Room methods */
Room * createRoom(int x, int y, int height, int width);
int drawRoom(Room * room);
int connectDoors(Position * doorOne,  Position * doorTwo);


#endif