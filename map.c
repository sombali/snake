#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include "map.h"

int mapSize;

//void mapppppp(){
//    int x, y;
//    for (x = 0; x < 50; x++) {
//        gotoxy(x, 0);
//        printf("/");
//    }
//
//    for (y = 1; y < 20; y++) {
//        for (x = 0; x < 2; x++) {
//            gotoxy(x, y);
//            printf("/");
//        }
//        for (x = 3; x < 48; x++) {
//            gotoxy(x, y);
//            printf(" ");
//        }
//        for (x = 48; x < 50; x++) {
//            gotoxy(x, y);
//            printf("/");
//        }
//    }
//
//    for (x = 0; x < 50; x++) {
//        gotoxy(x, 20);
//        printf("/");
//    }
//}
/**
 * Megrajzolja a pálya egyik részét.
 */
void map1(int size) {
    if (size == 1){
        return;
    } else {
        printf("/");
            return map1(size-1);
    }
}

/**
 * Megrajzolja a pálya másik részét.
 */
void map2(int edge) {
    int i;
    printf("//");
    for (i = 0; i < edge-5; i++){
        printf(" ");
    }
    printf("//\n");
}

/**
 * Felteszi a pálya méretére a kérdést.
 */
void drawQuestion() {
    gotoxy(25, 10);
    printf("Milyen nagyra szeretned a palyat? ");
    scanf("%d", &mapSize);
    clrScr();
}

/**
 * Kirajzolja a pályát.
 */
void drawMap() {
    int i, edge;
    edge = mapSize/3;
    map1(mapSize);
    printf("\n");
    for (i = 0; i < edge; i++){
        map2(mapSize);
    }
    map1(mapSize);
}

void drawScore(int score) {
    gotoxy(0, (mapSize/3 +3));
    printf("Score: %d", score);
}

void drawMultiScore(int score) {
    gotoxy(20, (mapSize/3 +3));
    printf("Score: %d", score);
}
