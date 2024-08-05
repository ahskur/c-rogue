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
Room ** mapSetup();
/* Here is declaring the method that returns a pointer to the struct Player*/
Player * playerSetup();
int playerMove(int y, int x, Player * user);
int playerInput(int input, Player * user);
int checkPosition(int newY, int newX, Player * user);

/* Room methods */
Room * createRoom(int x, int y, int height, int width);
int drawRoom(Room * room);
int connectDoors(Position * doorOne,  Position * doorTwo);

int main() {
    Player * user;
    int ch;

    // No idea what this truly does - Initialize rand?
    srand(time(NULL));

    screenSetup();
    mapSetup();
    user = playerSetup();
    /* Wait for user input before closing */
    /* main game loop */
    while ((ch = getch()) != 'm') 
    {
    /* Pass the key to the method and the user obj*/
    playerInput(ch, user);
    };
    endwin();
    return 1;
}

int screenSetup(){
    initscr();
    printw("Hello there!\nThis is a Rogue clone!\nPress WASD to Walk.");
    /* Noecho prevent inputs from writing to the screen */
    noecho();
    refresh();
    return 0;
}

Room ** mapSetup() {

    /* Create array of rooms to keep track of them*/
    Room ** rooms;
    rooms = malloc(sizeof(Room)*6);

    rooms[0]= createRoom(13, 13, 6, 16);
    drawRoom(rooms[0]);

    rooms[1]= createRoom(40, 2, 6, 8);
    drawRoom(rooms[1]);

    rooms[2]= createRoom(40, 10, 6, 12);
    drawRoom(rooms[2]);

    connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]);
    connectDoors(rooms[1]->doors[2], rooms[0]->doors[0]);


    return rooms;
}

Player * playerSetup() {
    Player * newPlayer;
    newPlayer = malloc(sizeof(Player));
    /*
    The -> operator is used to access members of a struct or union through a pointer.
    It is shorthand for dereferencing the pointer and then accessing the member.
    The -> operator is equivalent to dereferencing the pointer 
    and then using the dot operator. Like:
    (*newPlayer).position.y = 10;
     */
    newPlayer->position.x = 14;
    newPlayer->position.y = 14;
    newPlayer->health = 20;
    playerMove(14,14, newPlayer);
    return newPlayer;
}

int playerInput(int input, Player * user) {
    int newY;
    int newX;
    switch(input) {

        /*move up*/
        case 'W':
        case 'w':
            newY = user->position.y - 1;
            newX = user->position.x;
            break;
        /*move down*/
        case 'S':
        case 's':
            newY = user->position.y + 1;
            newX = user->position.x;           
            break;
        /*move left*/
        case 'A':        
        case 'a': 
            newY = user->position.y;
            newX = user->position.x - 1;
            break;
        /*move right*/
        case 'D':        
        case 'd':    
            newY = user->position.y;
            newX = user->position.x + 1;
            break;
        /* does nothing*/
        default:
            break;

    };
    checkPosition(newY,newX, user); 
}

int playerMove(int y, int x, Player * user) {
    mvprintw(user->position.y,user->position.x, ".");
    user->position.y = y;
    user->position.x = x;
    mvprintw(user->position.y,user->position.x, "@");
    move(user->position.y,user->position.x);
    refresh();

}
/* check what is at next pos */
int checkPosition(int newY, int newX, Player * user) {
    int space;
    switch(mvinch(newY,newX)) {
        case '.':
        case '#':
        case '+':
            playerMove(newY,newX, user);
            break;
        default:
            move(user->position.y, user->position.x);
            break;
    }
}

Room * createRoom(int x, int y, int height, int width) {
    Room * newRoom;
    newRoom = malloc(sizeof(Room));

    newRoom->position.x = x;
    newRoom->position.y = y;
    newRoom->height = height;
    newRoom->width = width;



    newRoom->doors = malloc(sizeof(Position)*4);


    // top doors
    newRoom->doors[0] = malloc(sizeof(Position));
    newRoom->doors[0]->x = rand() % (width - 2) + newRoom->position.x + 1; //random value in range of 0 to width
    newRoom->doors[0]->y = newRoom->position.y; //random value in range of 0 to width

    // left doors
    newRoom->doors[1] = malloc(sizeof(Position));
    newRoom->doors[1]->x = newRoom->position.x; //random value in range of 0 to width
    newRoom->doors[1]->y = rand() % (height-2) + newRoom->position.y + 1; //random value in range of


    // bottom doors
    newRoom->doors[2] = malloc(sizeof(Position));
    newRoom->doors[2]->x = rand() % (width - 2) + newRoom->position.x + 1; //random value in range of 0 to width
    newRoom->doors[2]->y = newRoom->position.y + newRoom->height - 1; //random value in range of 0 to width


    // right doors
    newRoom->doors[3] = malloc(sizeof(Position));
    newRoom->doors[3]->x = newRoom->position.x + width - 1; //random value in range of 0 to width
    newRoom->doors[3]->y = rand() % (height-2) + newRoom->position.y + 1; //random value in range of

    return newRoom;
}

int drawRoom(Room * room) {
    int x;
    int y;
    // draw top and botton
    for (x = room->position.x; x < room->position.x + room->width; x++) {
        mvprintw(room->position.y, x, "-");
        mvprintw(room->position.y+room->height -1, x, "-");
    }
    // draw walls
    for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++) {
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");
        for (x = room->position.x + 1; x< room->position.x + room->width -1; x++){
            // draw floor
            mvprintw(y,x,".");
        }
    }
    // draw doorss
    mvprintw(room->doors[0]->y,room->doors[0]->x,"+");
    mvprintw(room->doors[1]->y,room->doors[1]->x,"+");
    mvprintw(room->doors[2]->y,room->doors[2]->x,"+");
    mvprintw(room->doors[3]->y,room->doors[3]->x,"+");



    // return 1 on success
    return 1;
}

int connectDoors(Position * doorOne, Position * doorTwo)
{
    Position temp;
    Position previous;

    int count = 0;

    temp.x = doorOne->x;
    temp.y = doorOne->y;

    previous = temp;

    while(1)
    {
        // setp left
        if ((abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x - 1) == ' '))
        {
            previous.x = temp.x;
            temp.x = temp.x - 1;

        } else if ((abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x + 1) == ' '))
        {
            previous.x = temp.x;
            temp.x = temp.x + 1;

        } else if ((abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y + 1, temp.x) == ' '))
        {
            previous.y = temp.y;
            temp.y = temp.y + 1;
        } else if ((abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y - 1, temp.x) == ' '))
        {
            previous.y = temp.y;
            temp.y = temp.y - 1;
        } else {
            if (count == 0) {
                temp = previous;
                count++;
                continue;
            }

            return 0;
        }

        mvprintw(temp.y, temp.x, "#");
    }

    return 1;
}

