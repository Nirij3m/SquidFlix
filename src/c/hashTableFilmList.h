//
// Created by nirin on 5/12/2023.
//
#include "listDirector.h"
#include "listFilm.h"
#include "hashTableDirectorList.h"
#include <time.h>
#ifndef Film
#define Film

struct HashTableFilm {
    unsigned int items;
    unsigned int buckets;
    struct ListFilm** table;
};


struct HashTableFilm* createEmptyHashTableFilm(unsigned int buckets);
bool isHashTableEmptyFilm(struct HashTableFilm* ht);
unsigned int hashTableElementsFilm(struct HashTableFilm* ht);
int hash_functionFilm(struct HashTableFilm* ht, char* title);
int hash_functionGenre(struct HashTableFilm* ht, char* genre);
// Inserts "value" in the table. If no collision, it returns True, otherwise False
bool insertFilmRead(struct HashTableFilm* ht, char* title, int duration, char* genre);
bool insertFilmGenre(struct HashTableFilm* ht, char* genre, int duration, char* title);

bool existsFilm(struct HashTableFilm* ht, char* genre);
void printHashTableFilm(struct HashTableFilm* ht);
void deleteItemFilm(struct HashTableFilm* ht, char* title);
void deleteHashTableFilm(struct HashTableFilm** ht);
// Shows the whole content of the table as a histogram
// For each bucket, print a '*' to indicate an item

#endif //Film
