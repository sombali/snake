#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include "snake.h"
#include "map.h"

bool gameOver;

void drawFood (Coordinate cord) {
    gotoxy(cord.x, cord.y);
    printf("o");
}

Coordinate generateNewFoodPlace() {
    Coordinate result;
    srand(time(0));
    result.x = rand() % mapSize;
    if (result.x == 0) {
        result.x += 2;
    }
    else if (result.x == 1) {
        result.x += 1;
    }
    else  if (result.x >= mapSize - 3) {
        result.x -= 5;
    }
    else if (result.x == mapSize -4) {
        result.x -= 1;
    }

    result.y = rand() % mapSize/3;
    if (result.y == 0) {
        result.y += 1;
    }
    else if (result.y == mapSize/3) {
        result.y -= 1;
    }
    return result;
}

void drawMenu(int* menu) {
    gotoxy(35,10);
    printf("1. Start Game\n");
    gotoxy(35,12);
    printf("2. Records\n");
    gotoxy(35,14);
    printf("3. Quit\n");

    scanf("%d", menu);
    fflush(stdin);
    clrScr();
}

/**
 * Létrehoz a láncolt lista végére
 * egy új elemet.
 */
SnakeElement *addSnakeElementToList(SnakeElement *head, Coordinate cord) {
    SnakeElement *newElement;
    newElement = (SnakeElement*) malloc(sizeof(SnakeElement));
    newElement->cord = cord;
    newElement->next = NULL;
    newElement->before = NULL;

    if (head == NULL) {
        return newElement;
    }

    SnakeElement *iterator;
    for(iterator = head; iterator->next != NULL; iterator = iterator->next);
    iterator->next = newElement;
    newElement->before = iterator;
    return head;
}

/**
 * A kígyó kezdeti helyét adja meg.
 */
SnakeElement *buildStarterSnake(SnakeElement *head) {
    int i;
    int cordX = 4;
    for (i = 0; i < STARTER_SNAKE_SIZE_WITH_HEAD; i++) {
        Coordinate cord;
        cord.x = cordX++;
        cord.y = 4;
        head = addSnakeElementToList(head, cord);
    }
    return head;
}

SnakeElement *buildStarterSecondSnake(SnakeElement *secondhead) {
    int i;
    int cordX = 8;
    for (i = 0; i < STARTER_SNAKE_SIZE_WITH_HEAD; i++) {
        Coordinate cord;
        cord.x = cordX++;
        cord.y = 7;
        secondhead = addSnakeElementToList(secondhead, cord);
    }
    return secondhead;
}

/**
 * Kirajzolja a kígyót.
 */
void drawSnake(SnakeElement *head) {
    SnakeElement *iterator;
    for(iterator = head; iterator != NULL; iterator = iterator->next) {
        gotoxy(iterator->cord.x, iterator->cord.y);
        if(iterator == head) {
            printf("%c", '@');
        } else {
            printf("%c", '*');
        }
    }
}

void drawSecondSnake(SnakeElement *secondhead) {
    SnakeElement *iterator;
    for(iterator = secondhead; iterator != NULL; iterator = iterator->next) {
        gotoxy(iterator->cord.x, iterator->cord.y);
        if(iterator == secondhead) {
            printf("%c", '@');
        } else {
            printf("%c", ':');
        }
    }
}

void changeSnakeElementExceptHead(SnakeElement *head) {
    SnakeElement *iterator, *iteratorBack;
    for(iterator = head; iterator->next != NULL; iterator = iterator->next)
        ;
    for(iteratorBack = iterator; iteratorBack->before != NULL; iteratorBack = iteratorBack->before) {
        iteratorBack->cord = iteratorBack->before->cord;
    }
}

/**
 * Irányítás
 */
SnakeElement *moveSnake(SnakeElement *head, char direction) {
    switch(direction) {
    case 'w':
    case 'W':
        if (head->cord.y > 1) {
            changeSnakeElementExceptHead(head);
            head->cord.y = head->cord.y - 1;
        } else {
            gameOver = true;
        }
        break;
    case 's':
    case 'S':
        if (head->cord.y <= (mapSize/3) - 1) {
            changeSnakeElementExceptHead(head);
            head->cord.y = head->cord.y + 1;
        } else {
            gameOver = true;
        }
        break;
    case 'a':
    case 'A':
        if(head->cord.x >= 3) {
            changeSnakeElementExceptHead(head);
            head->cord.x = head->cord.x - 1;
        } else {
            gameOver = true;
        }
        break;
    case 'd':
    case 'D':
        if(head->cord.x <= mapSize - 5) {
            changeSnakeElementExceptHead(head);
            head->cord.x = head->cord.x + 1;
        } else {
            gameOver = true;
        }
        break;
    }
    return head;
}

SnakeElement *moveSecondSnake (SnakeElement *secondhead, char direction) {
    switch(direction) {
    case UP:
        if (secondhead->cord.y > 1) {
            changeSnakeElementExceptHead(secondhead);
            secondhead->cord.y = secondhead->cord.y - 1;
        } else {
            gameOver = true;
        }
        break;
    case DOWN:
        if (secondhead->cord.y <= (mapSize/3) - 1) {
            changeSnakeElementExceptHead(secondhead);
            secondhead->cord.y = secondhead->cord.y + 1;
        } else {
            gameOver = true;
        }
        break;
    case LEFT:
        if(secondhead->cord.x >= 3) {
            changeSnakeElementExceptHead(secondhead);
            secondhead->cord.x = secondhead->cord.x - 1;
        } else {
            gameOver = true;
        }
        break;
    case RIGHT:
        if(secondhead->cord.x <= mapSize - 5) {
            changeSnakeElementExceptHead(secondhead);
            secondhead->cord.x = secondhead->cord.x + 1;
        } else {
            gameOver = true;
        }
        break;
    }
    return secondhead;
}

void Death (SnakeElement *head) {
    SnakeElement *iterator;
    iterator = head->next;
    while(iterator != NULL)
    {
        if(head->cord.x == iterator->cord.x && head->cord.y == iterator->cord.y)
        {
            gameOver = true;
        }
        iterator = iterator->next;
    }
}

void singlePlayer (SnakeElement *head) {
    Coordinate foodCord = {3, 3};
    int snakeFoodCounter = 1;
    int score = 0;
    SnakeElement *iterator;
    char name[20];
    gameOver = false;
    drawQuestion();
    drawMap();
    //mapppppp();
    head = buildStarterSnake(head);
    drawSnake(head);
    char direction;
    getch();
    while(1) {
        if (kbhit()) {
            direction = getch();
        }
        if(gameOver) {
            clrScr();
            freeSnakeList(head);
            printf("Game Over... HaHaHa...");
            getch();
            clrScr();
            printf("Enter your name: ");
            scanf("%s", &name);
            saveRecords(score, name);
            return;
        }
        if(head->cord.x == foodCord.x && head->cord.y == foodCord.y) {
                            if(++snakeFoodCounter == 5) {
                                for(iterator = head; iterator->next != NULL; iterator = iterator->next);
                                Coordinate newCord;
                                newCord.x = iterator->cord.x;
                                newCord.y = iterator->cord.y + 1;
                                addSnakeElementToList(head, newCord);
                                snakeFoodCounter = 1;
                            }
            foodCord = generateNewFoodPlace();
            score += 10;
        }
        head = moveSnake(head, direction);
        //mapppppp();
        drawSnake(head);
        Death(head);
        drawFood(foodCord);
        drawScore(score);
        Sleep(100);
        clrScr();
        drawMap();
        //clrScrExceptMap();
    }
}

void freeSnakeList(SnakeElement *first) {
    SnakeElement *iterator = first;
    while (iterator != NULL) {
       SnakeElement *temp = iterator->next;
       free(iterator);
       iterator = temp;
    }
    first = NULL;
}

void MultiPlayer(SnakeElement *head, SnakeElement *secondhead) {
    Coordinate foodCord = {3, 3};
    int snakeFoodCounter1 = 1;
    int snakeFoodCounter2 = 1;
    int score1 = 0;
    int score2 = 0;
    SnakeElement *iterator;
    char name[20];
    gameOver = false;
    drawQuestion();
    drawMap();
    //mapppppp();
    head = buildStarterSnake(head);
    secondhead = buildStarterSecondSnake(secondhead);
    drawSnake(head);
    drawSecondSnake(secondhead);
    char direction1;
    char direction2;
    char tempDirection;
    getch();
    while(1) {
        if (kbhit()) {
            tempDirection = getch();
            switch(tempDirection) {
            case 'A':
            case 'W':
            case 'S':
            case 'D':
            case 'a':
            case 'w':
            case 's':
            case 'd':
                direction1 = tempDirection;
                break;
            case UP:
            case DOWN:
            case LEFT:
            case RIGHT:
                direction2 = tempDirection;
                break;
            }
        }
        if(gameOver) {
            clrScr();
            freeSnakeList(head);
            freeSnakeList(secondhead);
            printf("Game Over... HaHaHa...");
            getch();
            clrScr();
            printf("Enter your name: ");
            scanf("%s", &name);
            saveRecords(score1, name);
            return;
        }
        if(head->cord.x == foodCord.x && head->cord.y == foodCord.y) {
                            if(++snakeFoodCounter1 == 5) {
                                for(iterator = head; iterator->next != NULL; iterator = iterator->next);
                                Coordinate newCord;
                                newCord.x = iterator->cord.x;
                                newCord.y = iterator->cord.y + 1;
                                addSnakeElementToList(head, newCord);
                                snakeFoodCounter1 = 1;
                            }
            foodCord = generateNewFoodPlace();
            score1 += 10;
        }
        if(secondhead->cord.x == foodCord.x && secondhead->cord.y == foodCord.y) {
                            if(++snakeFoodCounter2 == 5) {
                                for(iterator = secondhead; iterator->next != NULL; iterator = iterator->next);
                                Coordinate newCord;
                                newCord.x = iterator->cord.x;
                                newCord.y = iterator->cord.y + 1;
                                addSnakeElementToList(secondhead, newCord);
                                snakeFoodCounter2 = 1;
                            }
            foodCord = generateNewFoodPlace();
            score2 += 10;
        }
        head = moveSnake(head, direction1);
        secondhead = moveSecondSnake(secondhead, direction2);
        //mapppppp();
        drawSnake(head);
        drawSecondSnake(secondhead);
        Death(head);
        Death(secondhead);
        drawFood(foodCord);
        drawScore(score1);
        drawScore(score2);
        Sleep(100);
        clrScr();
        drawMap();
        //clrScrExceptMap();
    }
}
