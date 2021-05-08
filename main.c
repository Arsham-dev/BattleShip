#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct block {
    bool hit;
    bool isFull;
    bool CHit;
};
struct ship {
    char xFirst;
    char yFirst;
    char xLast;
    char yLast;
    bool payed;
    struct ship *next;
};
struct user {
    struct block *blocks;
    struct ship *ships;
    char *name;
    int numberOfRemainShip;
    int point;
};
struct users {
    struct user *structUser;
    struct users *next;
};
struct user *user1;
struct user *user2;
int length;
int numberOfUser;
struct users *allUser;
struct user *bot;

//Build user bot for playing with bot
struct user *buildBot();

void setShipForBot();

void emptyMap(struct user *structUser);

void playGame1vs1();

inline void addPart(unsigned short x, unsigned short y, struct user *structUser);

void setShip(struct ship Ship, struct user *structUser);

inline bool hit(unsigned short x, unsigned short y, struct user *structUser);

void printBlock(struct block *structBlock);

void printAll(struct user *structUser);

bool getHit(struct user *structUser);

void destroyedShip(struct ship *structShip, struct user *structUser);

inline void destroyedPartOfShip(unsigned short x, unsigned short y, struct user *structUser);

void changeLength(unsigned short x);

inline bool checkBlock(unsigned short x, unsigned short y, struct user *structUser);

bool checkShip(struct ship structShip, struct user *structUser);

struct ship *getShip(struct user *structUser, int size);

bool checkCanBuildShip(struct ship structShip, struct user *structUser);

bool checkBlockArea(unsigned int x, unsigned int y, struct user *structUser);

void setShipForUser(struct user *structUser);

struct user *buildUser();

void printAllUser();

struct user *getUser(int number);

void playWithBot();

bool checkBlockIsFull(unsigned int x, unsigned int y, struct user *structUser) {
    if (x < 0 || x > 9 || y < 0 || y > 9)
        return false;
    else
        return structUser->blocks[x * length + y].isFull;
}

struct ship *buildShip(unsigned int xFirst, unsigned int yFirst, unsigned int xLast, unsigned int yLast);

void printMenu() {
    printf("1-Play with a Friend\n");
    printf("2-Play with bot\n");
    printf("3-Load game\n");
    printf("4-Load last game\n");
    printf("5-Settings\n");
    printf("6-Score Board\n");
    printf("7-Exit\n");
}

int main() {
    bool checker = true;
    numberOfUser = 0;
    length = 10;
    allUser = (struct users *) malloc(sizeof(struct users));
    allUser->next = NULL;
    int command;
    while (checker) {
        printMenu();
        scanf("%d", &command);
        switch (command) {
            case 1:
                printf("First player\n");
                printf("choose user\n");
                int com1;
            F1:
                printf("1. choose from available users\n");
                printf("2. new user\n");

                scanf("%d", &com1);
                switch (com1) {
                    case 1:
                        printAllUser();
                        int userInt;
                        printf("Enter number of user\n");
                        scanf("%d", &userInt);
                        if (userInt > numberOfUser) {
                            goto F1;
                        }
                        user1 = getUser(userInt);
                        break;
                    case 2:
                        user1 = buildUser();
                        break;
                    default:
                        printf("try again\n");
                        goto F1;
                }
                printf("Second player\n");
                printf("choose user\n");
                int com2;
            F2:
                printf("1. choose from available users\n");
                printf("2. new user\n");
                scanf("%d", &com2);
                switch (com2) {
                    case 1:
                        printAllUser();
                        int userInt;
                        printf("Enter number of user\n");
                        scanf("%d", &userInt);
                        if (userInt > numberOfUser) {
                            goto F2;
                        }
                        user2 = getUser(userInt);
                        break;
                    case 2:
                        user2 = buildUser();
                        break;
                    default:
                        printf("try again\n");
                        goto F2;
                }
                playGame1vs1();
                break;
            case 2:

                printf("First player\n");
                printf("choose user\n");
                int com3;
            F3:
                printf("1. choose from available users\n");
                printf("2. new user\n");

                scanf("%d", &com3);
                switch (com3) {
                    case 1:
                        printAllUser();
                        int userInt;
                        printf("Enter number of user\n");
                        scanf("%d", &userInt);
                        if (userInt > numberOfUser) {
                            goto F3;
                        }
                        user1 = getUser(userInt);
                        break;
                    case 2:
                        user1 = buildUser();
                        break;
                    default:
                        printf("try again\n");
                        goto F3;
                }

                bot = buildBot();
                playWithBot();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                printf("1-mapSize\n");
                int com4;
                scanf("%d", &com4);
                if (com4 == 1) {
                    printf("Enter new size\n");
                    int x;
                    scanf("%d", &x);
                    changeLength(x);
                }
                break;
            case 6:
                printAllUser();
                break;
            case 7:
                checker = false;
                printf("Bye\n");
                break;
        }
    }
    return 0;
}


void addPart(unsigned short x, unsigned short y, struct user *structUser) {
    structUser->blocks[x * length + y].isFull = true;
}

bool hit(unsigned short x, unsigned short y, struct user *structUser) {
    structUser->blocks[x * length + y].hit = true;
    struct ship *s = structUser->ships;
    while (s != NULL) {
        if (checkShip(*s, structUser))
            destroyedShip(s, structUser);
        s = s->next;
    }
    return structUser->blocks[x * length + y].isFull;
}

void printBlock(struct block *structBlock) {
    if (structBlock->hit == false)
        printf(" (   ) ");
    else if (structBlock->CHit == true)
        printf(" ( C ) ");
    else if (structBlock->isFull == true)
        printf(" ( E ) ");
    else if (structBlock->isFull == false)
        printf(" ( W ) ");
}

void printAll(struct user *structUser) {
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            printBlock(&structUser->blocks[i * length + j]);
        }
        printf("\n");
    }
}

bool getHit(struct user *structUser) {
    printf("enter X\n");
    unsigned short x;
    scanf("%hd", &x);
    printf("enter Y\n");
    unsigned short y;
    scanf("%hd", &y);
    if (x >= 10 || y >= 10) {
        printf("Out of range ,Choose again\n");
        return getHit(structUser);
    } else if (structUser->blocks[x * length + y].hit == true) {
        printf("Can't hit again ,Choose again\n");
        return getHit(structUser);
    } else
        return hit(x, y, structUser);

}

bool getRandomHit(struct user *structUser) {
    int x, y;
    x = rand() % 10;
    y = rand() % 10;
    if (structUser->blocks[x * length + y].hit == true)
        return getRandomHit(structUser);
    else
        return hit(x, y, structUser);
}

void changeLength(unsigned short x) {
    length = x;
    printf("Size changed\n");
}

void setShip(struct ship structShip, struct user *structUser) {
    if (structShip.xFirst == structShip.xLast)
        for (int i = structShip.yFirst; i <= structShip.yLast; ++i) {
            addPart(structShip.xFirst, i, structUser);
        }
    else
        for (int i = structShip.xFirst; i <= structShip.xLast; ++i) {
            addPart(i, structShip.yFirst, structUser);
        }
}

void destroyedPartOfShip(unsigned short x, unsigned short y, struct user *structUser) {
    structUser->blocks[x * length + y].CHit = true;
}

void destroyedShip(struct ship *structShip, struct user *structUser) {
    if (structShip->payed)
        return;
    int size = 0;
    if (structShip->xFirst == structShip->xLast) {
        hit(structShip->xFirst + 1, structShip->yFirst - 1, structUser);
        hit(structShip->xFirst, structShip->yFirst - 1, structUser);
        hit(structShip->xFirst - 1, structShip->yFirst - 1, structUser);
        for (int i = structShip->yFirst; i <= structShip->yLast; ++i) {
            destroyedPartOfShip(structShip->xFirst, i, structUser);
            hit(structShip->xFirst + 1, i, structUser);
            hit(structShip->xFirst - 1, i, structUser);
        }
        hit(structShip->xFirst + 1, structShip->yLast + 1, structUser);
        hit(structShip->xFirst, structShip->yLast + 1, structUser);
        hit(structShip->xFirst - 1, structShip->yLast + 1, structUser);
        if (!structShip->payed) {
            structShip->payed = true;
            size = structShip->yLast - structShip->yFirst + 1;
        }
    } else {
        hit(structShip->xFirst - 1, structShip->yFirst + 1, structUser);
        hit(structShip->xFirst - 1, structShip->yFirst, structUser);
        hit(structShip->xFirst - 1, structShip->yFirst - 1, structUser);
        for (int i = structShip->xFirst; i <= structShip->xLast; ++i) {
            destroyedPartOfShip(i, structShip->yFirst, structUser);
            hit(i, structShip->yFirst + 1, structUser);
            hit(i, structShip->yFirst - 1, structUser);
        }
        hit(structShip->xLast + 1, structShip->yFirst + 1, structUser);
        hit(structShip->xLast + 1, structShip->yFirst, structUser);
        hit(structShip->xLast + 1, structShip->yFirst - 1, structUser);
        if (!structShip->payed) {
            structShip->payed = true;
            size = structShip->xLast - structShip->xFirst + 1;
        }
    }
    if (size == 5)
        structUser->point += 5;
    else if (size == 3)
        structUser->point += 8;
    else if (size == 2)
        structUser->point += 12;
    else if (size == 1)
        structUser->point += 25;


}

bool checkBlock(unsigned short x, unsigned short y, struct user *structUser) {
    return structUser->blocks[length * x + y].hit;
}

bool checkShip(struct ship structShip, struct user *structUser) {
    if (structShip.xFirst == structShip.xLast)
        for (int i = structShip.yFirst; i <= structShip.yLast; ++i) {
            if (!checkBlock(structShip.xFirst + i, structShip.yFirst, structUser))
                return false;
        }
    else
        for (int i = structShip.xFirst; i <= structShip.xLast; ++i) {
            if (!checkBlock(structShip.xFirst + i, structShip.yFirst, structUser))
                return false;
        }
    return true;
}

struct ship *getShip(struct user *structUser, int size) {
    int xFirst, xLast, yFirst, yLast;
    printf("Enter x first\n");
    scanf("%d", &xFirst);
    printf("Enter y first\n");
    scanf("%d", &yFirst);
    printf("Enter x last\n");
    scanf("%d", &xLast);
    printf("Enter y last\n");
    scanf("%d", &yLast);
    //new ship
    struct ship *structShip = (struct ship *) malloc(sizeof(struct ship));
    //swap x to manage ship
    if (xFirst > xLast) {
        int temp = xFirst;
        xFirst = xLast;
        xLast = temp;
    }
    if (yFirst > yLast) {
        int temp = yFirst;
        yFirst = yLast;
        yLast = temp;
    }
    structShip->xFirst = (char) xFirst;
    structShip->xLast = (char) xLast;
    structShip->yFirst = (char) yFirst;
    structShip->yLast = (char) yLast;
    structShip->next = NULL;
    structShip->payed = false;
    if (xLast - xFirst + yLast - yFirst != size - 1) {
        printf("Size of ship isn't correct try again\n");
        free(structShip);
        return getShip(structUser, size);
    } else if (!checkCanBuildShip(*structShip, structUser)) {
        printf("Can't set choose another location\n");
        free(structShip);
        return getShip(structUser, size);
    } else {
        if (structUser->ships == NULL) {
            structUser->ships = structShip;
        } else {
            struct ship *s = structUser->ships;
            while (s->next != NULL)
                s = s->next;
            s->next = structShip;
        }
        setShip(*structShip, structUser);
        printf("Ship set\n");
        //increase numberOfRemainShip
        structUser->numberOfRemainShip++;
        return structUser->ships;
    }
}

bool checkBlockArea(unsigned int x, unsigned int y, struct user *structUser) {
    if (checkBlockIsFull(x, y, structUser))
        return false;
    else if (checkBlockIsFull(x, y + 1, structUser))
        return false;
    else if (checkBlockIsFull(x, y - 1, structUser))
        return false;
    else if (checkBlockIsFull(x + 1, y, structUser))
        return false;
    else if (checkBlockIsFull(x + 1, y + 1, structUser))
        return false;
    else if (checkBlockIsFull(x + 1, y - 1, structUser))
        return false;
    else if (checkBlockIsFull(x - 1, y, structUser))
        return false;
    else if (checkBlockIsFull(x - 1, y + 1, structUser))
        return false;
    else if (checkBlockIsFull(x - 1, y - 1, structUser))
        return false;
    else
        return true;
}

bool checkCanBuildShip(struct ship structShip, struct user *structUser) {
    if (structShip.xFirst == structShip.xLast)
        for (int i = structShip.yFirst; i <= structShip.yLast; ++i) {
            if (!checkBlockArea(structShip.xFirst, i, structUser))
                return false;
        }
    else
        for (int i = structShip.xFirst; i <= structShip.xLast; ++i) {
            if (!checkBlockArea(i, structShip.yFirst, structUser))
                return false;
        }

    return structShip.xFirst == structShip.xLast || structShip.yFirst == structShip.yLast;
}

void setShipForUser(struct user *structUser) {
    structUser->ships = NULL;
    printf("Enter location of ship with length of 5\n");
    structUser->ships = getShip(structUser, 5);
    for (int i = 0; i < 2; ++i) {
        printf("Enter location of ship with length of 3\n");
        structUser->ships = getShip(structUser, 3);
    }
    for (int i = 0; i < 3; ++i) {
        printf("Enter location of ship with length of 2\n");
        structUser->ships = getShip(structUser, 2);
    }
    for (int i = 0; i < 4; ++i) {
        printf("Enter location of ship with length of 1\n");
        structUser->ships = getShip(structUser, 1);
    }
}

void playWithBot() {
    printf("User1 start set Ships\n");
    setShipForUser(user1);
    while (user1->numberOfRemainShip != 0 && bot->numberOfRemainShip != 0) {
        //user1 turn
        F1:
        printf("Bot map\n");
        printAll(bot);
        printf("%s turn\n", user1->name);
        bool check = getHit(bot);
        printf("Bot map\n");
        printAll(bot);
        if (check) {
            user1->point++;
            goto F1;
        }
        F2:
        if (getRandomHit(user1))
            goto F2;
    }
    if (bot->numberOfRemainShip == 0) {
        printf("user1 won\n");
        bot->point /= 2;
    } else {
        printf("bot won\n");
        user1->point /= 2;
    }
    emptyMap(user1);
    emptyMap(bot);
    printAllUser();
}

void playGame1vs1() {
    printf("User1 start set Ships\n");
    setShipForUser(user1);
    printf("User2 start set Ships\n");
    setShipForUser(user2);
    while (user1->numberOfRemainShip != 0 && user2->numberOfRemainShip != 0) {
        //user1 turn
        F1:
        printf("User1 map\n");
        printAll(user1);
        printf("%s turn\n", user2->name);
        bool check = getHit(user1);
        printf("User1 map\n");
        printAll(user1);
        if (check) {
            user2->point++;
            goto F1;
        }
        //user2 turn
        F2:
        printf("User2 map\n");
        printAll(user2);
        printf("%s turn\n", user1->name);
        check = getHit(user2);
        printf("User2 map\n");
        printAll(user2);
        if (check) {
            user1->point++;
            goto F2;
        }
    }
    if (user2->numberOfRemainShip == 0) {
        printf("user1 won\n");
        user2->point /= 2;
    } else {
        printf("user2 won\n");
        user1->point /= 2;
    }
    emptyMap(user1);
    emptyMap(user2);
    printAllUser();

}

struct user *buildUser() {
    struct user *u = (struct user *) malloc(sizeof(struct user));
    u->point = 0;
    u->numberOfRemainShip = 0;
    u->blocks = (struct block *) malloc(sizeof(struct block) * length * length);
    u->ships = NULL;
    printf("Enter name of user\n");
    char *arr = (char *) malloc(sizeof(char *) * 20);
    scanf("%s", arr);
    u->name = arr;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            u->blocks[i * length + j].hit = false;
            u->blocks[i * length + j].isFull = false;
            u->blocks[i * length + j].CHit = false;
        }
    }

    struct users *structUsers = allUser;
    if (numberOfUser == 0) {
        allUser->structUser = u;
        allUser->next = NULL;
        numberOfUser++;
        return u;
    }
    struct users *newUser = (struct users *) malloc(sizeof(struct users));
    newUser->structUser = u;
    newUser->next = NULL;
    while (structUsers->next != NULL)
        structUsers = structUsers->next;
    //set new user
    structUsers->next = newUser;
    numberOfUser++;
    return u;
}

void printAllUser() {
    if (numberOfUser == 0) {
        printf("There is no user\n");
        return;
    }
    struct users *structUsers = allUser;
    int i = 1;
    while (structUsers != NULL) {
        printf("%d-%s point is:%d\n", i, structUsers->structUser->name, structUsers->structUser->point);
        i++;
        structUsers = structUsers->next;
    }
}

struct user *getUser(int number) {
    struct users *structUsers = allUser;
    if (number < 1)
        return NULL;
    int num = 1;
    while (number != num) {
        structUsers = structUsers->next;
        num++;
    }
    return structUsers->structUser;
}

struct user *buildBot() {
    bot = (struct user *) malloc(sizeof(struct user));
    bot->point = 0;
    bot->numberOfRemainShip = 0;
    bot->blocks = (struct block *) malloc(sizeof(struct block) * length * length);
    bot->ships = NULL;
    char arr[] = "Bot";
    bot->name = arr;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            bot->blocks[i * length + j].hit = false;
            bot->blocks[i * length + j].isFull = false;
            bot->blocks[i * length + j].CHit = false;
        }
    }
    printf("Set ship for bot\n");
    setShipForUser(bot);
    return bot;
}

void emptyMap(struct user *structUser) {
    structUser->numberOfRemainShip = 0;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            structUser->blocks[i * length + j].hit = false;
            structUser->blocks[i * length + j].isFull = false;
            structUser->blocks[i * length + j].CHit = false;
        }
    }
}

struct ship *buildShip(unsigned int xFirst, unsigned int yFirst, unsigned int xLast, unsigned int yLast) {
    struct ship *structShip = (struct ship *) malloc(sizeof(struct ship));
    structShip->payed = false;
    structShip->xFirst = (char) xFirst;
    structShip->xLast = (char) xLast;
    structShip->yFirst = (char) yFirst;
    structShip->yLast = (char) yLast;
    return structShip;
}

