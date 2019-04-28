#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include "snake.h"

#define STARTER_SNAKE_SIZE_WITH_HEAD 4
#define STARTER_SECONDSNAKE_SIZE_WITH_HEAD 15

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

extern bool gameOver;

typedef struct Coordinate {
    int x;
    int y;
} Coordinate;

typedef struct SnakeElement {
    Coordinate cord;
    struct SnakeElement *next;
    struct SnakeElement *before;
} SnakeElement;

void drawFood (Coordinate cord);
Coordinate generateNewFoodPlace();
void drawMenu(int* menu);
SnakeElement *addSnakeElementToList(SnakeElement *head, Coordinate cord);
SnakeElement *buildStarterSnake(SnakeElement *head);
SnakeElement *buildStarterSecondSnake(SnakeElement *secondhead);
void drawSnake(SnakeElement *head);
void drawSecondSnake(SnakeElement *secondhead);
void changeSnakeElementExceptHead(SnakeElement *head);
SnakeElement *moveSnake(SnakeElement *head, char direction);
SnakeElement *moveSecondSnake (SnakeElement *secondhead, char direction);
void Death (SnakeElement *head);
void singlePlayer (SnakeElement *head);
void MultiPlayer(SnakeElement *head, SnakeElement *secondhead);

#endif // SNAKE_H_INCLUDED
