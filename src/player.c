#include <rogue.h>

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