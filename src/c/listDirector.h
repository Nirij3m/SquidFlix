

#ifndef DIRECTOR
#define DIRECTOR
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


struct Director {
    char* name;
    int nmbFilm;
    struct ListFilm** films;
    struct Director* next;
};

struct ListDirector{
    int size;
    struct Director* head;
    struct Director* topDirector;
};

struct Director* createCellDirector(char* name);
struct ListDirector* createEmptyListDirector();
void addFirstDirector(struct ListDirector* l, char* name);
bool isListEmptyDirector(struct ListDirector* l);
struct Director* getItemPosDirector(struct ListDirector* l, unsigned int position, bool* valid);
void deleteFirstDirector(struct ListDirector* l);
void printListDirector(struct ListDirector* l);
unsigned int listSizeDirector(struct ListDirector* l);
void addItemPosDirector(struct ListDirector* l, char* name, unsigned int position, bool* valid);
void deleteItemPosDirector(struct ListDirector* l, unsigned int position, bool* valid);
void deleteListDirector(struct ListDirector** l);
struct Director* directorBelongs(struct ListDirector* l, char* name);
struct Director* topDirector(struct ListDirector* ld);
int getPosItemDirector(struct ListDirector*l, char* name);

#endif
