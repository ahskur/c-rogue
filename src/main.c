#include <rogue.h>

int main() {
    Player * user;
    int ch;

    // No idea what this truly does - Initialize rand?
    srand(time(NULL));

    char ** level;

    screenSetup();


    level = saveLevelPos();


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
