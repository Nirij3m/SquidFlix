
#ifndef TP9EX2_LIST_H
#define TP9EX2_LIST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct CellFilm{
    char* nomFilm;
    int duration;
    char* genre;
    struct CellFilm* next;
};

struct ListFilm{
    char* director;
    unsigned int size;
    struct CellFilm* head;
};


struct CellFilm* createCellFilm(char* nomFilm, int duration, char* genre);
struct ListFilm* createEmptyListFilm();
void addFirstFilm(struct ListFilm* l, char* nomFilm, int duration, char* genre);
bool isListEmptyFilm(struct ListFilm* l);
struct CellFilm* getItemPosFilm(struct ListFilm* l, unsigned int position, bool* valid);
void deleteFirstFilm(struct ListFilm* l);
void printListFilm(struct ListFilm* l);
unsigned int listSizeFilm(struct ListFilm* l);
void addItemPosFilm(struct ListFilm* l, char* nomFilm, int duration, char* genre, unsigned int position, bool* valid);
void deleteItemPosFilm(struct ListFilm* l, unsigned int position, bool* valid);
void deleteListFilm(struct ListFilm** l);
struct CellFilm* filmBelongs(struct ListFilm* l, char* nomFilm, int duration, char* genre);

struct ListFilm** createTimeArray();
bool insertFilm(struct ListFilm** timeArray, char* title, int duration, char* genre);
void freeTimeArray(struct ListFilm** timeArray);
void printTimeArray(struct ListFilm** timeArray);


//int getPosItem(struct ListFilm*l, char* name, int nmbFilm);

#endif //TP9EX2_LIST_H
