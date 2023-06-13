
#ifndef TP9EX2_LIST_H
#define TP9EX2_LIST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct Director {
    char* name;
    int nmbFilm;
};

struct ListFilm{
    char* director;
    unsigned int size;
    struct CellFilm* head;
};

struct CellFilm{
    char* nomFilm;
    int duration;
    char* genre;
    struct CellFilm* next;
};

struct Director* createDirector(char* name);
struct CellFilm* createCellFilm(char* nomFilm, int duration, char* genre);
struct ListFilm* createEmptyListFilm();
void addFirstFilm(struct ListFilm* l, char* nomFilm, int duration, char* genre);
bool isListEmptyFilm(struct ListFilm* l);

void deleteFirstFilm(struct ListFilm* l);
void printListFilm(struct ListFilm* l);
unsigned int listSizeFilm(struct ListFilm* l);


void deleteListFilm(struct ListFilm** l);
void deleteDirector(struct Director* d);

struct ListFilm** createTimeArray();
bool insertFilm(struct ListFilm** timeArray, char* title, int duration, char* genre);
void freeTimeArray(struct ListFilm** timeArray);


#endif //TP9EX2_LIST_H
