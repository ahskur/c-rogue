#include <rogue.h>

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