#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "map.h"
#include "snake.h"

/**
 * Beállítja nullára a koordinátákat.
 */
COORD coord = {0, 0};

typedef struct RecordElement {
    char* name;
    int bestScore;
    struct RecordElement* next;
} RecordElement;

/**
 * A képernyő törlése.
 */
void clrScr() {
    system("@cls||clear");
}

void gotoxy (int x, int y) {
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

RecordElement* addNewRecord(RecordElement* firstRecord, RecordElement* newRecord) {
    newRecord->next = NULL;
    if(firstRecord == NULL) {
        return newRecord;
    }
    RecordElement* iterator;
    for(iterator = firstRecord; iterator->next != NULL; iterator = iterator->next);
    iterator->next = newRecord;
    return firstRecord;
}

RecordElement* sortRecordListElement(RecordElement* firstRecord, int listSize) {
    RecordElement* iterator;
    int i;
    for(i = 0; i < listSize; i++) {
        for(iterator = firstRecord; iterator->next != NULL; iterator = iterator->next) {
            if(iterator->bestScore < iterator->next->bestScore){
                int tempBestScore = iterator->next->bestScore;
                char* nameTemp = (char*) malloc(20 * sizeof(char));
                nameTemp = iterator->next->name;
                iterator->next->bestScore = iterator->bestScore;
                iterator->next->name = iterator->name;
                iterator->bestScore = tempBestScore;
                iterator->name = nameTemp;
            }
        }
    }
    return firstRecord;
}

void printRecords(RecordElement* firstRecord) {
    RecordElement* iterator;
    int counter = 0;
    for(iterator = firstRecord; iterator != NULL && counter < 3; iterator = iterator->next, counter++) {
        printf("%s: %d\n", iterator->name, iterator->bestScore);
    }
}

RecordElement* readRecords(RecordElement* firstRecord) {
    char buffer[20];
    int number;
    int counter = 0;
    FILE* f = fopen("record.txt", "r");
    while(fgets(buffer, 19, f)) {
        RecordElement* newRecord = (RecordElement*) malloc(sizeof(RecordElement));
        newRecord->name = (char*) malloc(20 * sizeof(char));
        strcpy(newRecord->name, buffer);
        newRecord->name[strlen(buffer)-1]='\0';
        fgets(buffer, 19, f);
        sscanf(buffer, "%d", &number);
        newRecord->bestScore = number;
        firstRecord = addNewRecord(firstRecord, newRecord);
        counter++;
    }
    firstRecord = sortRecordListElement(firstRecord, counter);
    return firstRecord;
}

void saveRecords(int score, char *name) {
    FILE *record;
    record = fopen("record.txt", "a");

    if (record == NULL) {
        perror("Nem sikerult megnyitni a file-t.");
        return;
    }

    fprintf(record, "%s\n%d\n", name, score);
    fclose(record);
}

void freeRecordList(RecordElement* firstRecord) {
    RecordElement *iterator = firstRecord;
    while(iterator != NULL) {
        RecordElement* tempNext = iterator->next;
        free(iterator->name);
        free(iterator);
        iterator = tempNext;
    }
    firstRecord = NULL;
}

/**
 * Menü
 */
void executeMenuItem(int menu) {
    int game;
    SnakeElement *head = NULL;
    SnakeElement *secondhead = NULL;
    RecordElement *firstRecord = NULL;
    switch(menu){
        case 1:
            gotoxy(35, 10);
            printf("1. Single player\n");
            gotoxy(35, 12);
            printf("2. Multiplayer\n");
            scanf("%d", &game);
            clrScr();
            switch(game) {
                case 1:
                    singlePlayer(head);
                    break;
                case 2:
                    MultiPlayer(head, secondhead);
                    break;
                default :
                    printf("Wrong number\n");
                    break;
            }
        case 2:
            clrScr();
            firstRecord = readRecords(firstRecord);
            printRecords(firstRecord);
            getch();
            clrScr();
            freeRecordList(firstRecord);
            break;
        default:
            printf("Wrong number\n");
            break;
    }
}

int main() {
    int menu;
    drawMenu(&menu);
    while(menu != 3) {
        executeMenuItem(menu);
        drawMenu(&menu);
    }
    return 0;
}
