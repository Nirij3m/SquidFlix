#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifndef TP9EX2_LIST_H
#define TP9EX2_LIST_H

struct CellFilm{
    char* nomFilm;
    int duration;
    char* genre;
    struct CellFilm* next;
};

struct ListFilm{
    unsigned int size;
    struct CellFilm* head;
};

struct CellFilm* createCellFilm(char* nomFilm, int duration, char* genre);
struct ListFilm* createEmptyListFilm();
void addFirstFilm(struct ListFilm* l, char* nomFilm, int duration, char* genre);
bool isListEmpty(struct ListFilm* l);
struct CellFilm* getItemPosFilm(struct ListFilm* l, unsigned int position, bool* valid);
void deleteFirstFilm(struct ListFilm* l);
void printListFilm(struct ListFilm* l);
unsigned int listSize(struct ListFilm* l);
void addItemPosFilm(struct ListFilm* l, char* nomFilm, int duration, char* genre, unsigned int position, bool* valid);
void deleteItemPosFilm(struct ListFilm* l, unsigned int position, bool* valid);
void deleteListFilm(struct ListFilm** l);

struct CellFilm* filmBelongs(struct ListFilm* l, char* nomFilm, int duration, char* genre);

//int getPosItem(struct ListFilm*l, int value);

#endif //TP9EX2_LIST_H
