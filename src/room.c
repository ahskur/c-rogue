#include <rogue.h>


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
