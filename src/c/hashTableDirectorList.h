//
// Created by nirin on 5/12/2023.
//
#include "listDirector.h"
#include "listFilm.h"
#include <time.h>
#ifndef TP15_2_HASHISH_HASHTABLEINTLIST_H
#define TP15_2_HASHISH_HASHTABLEINTLIST_H

struct HashTable {
    unsigned int items;
    unsigned int buckets;
    struct ListDirector** table;
    struct Director* topDirector;
};


struct HashTable* createEmptyHashTable(unsigned int buckets);
bool isHashTableEmpty(struct HashTable* ht);
unsigned int hashTableElements(struct HashTable* ht);
int hash_function(struct HashTable* ht, char* director);
// Inserts "value" in the table. If no collision, it returns True, otherwise False
bool insert(struct HashTable* ht, char* director, char* title, int duration, char* genre, int* maxFilm);

bool exists(struct HashTable* ht, char* director);
void printHashTable(struct HashTable* ht);
void deleteItem(struct HashTable* ht, char* director);
void deleteHashTable(struct HashTable** ht);
// Shows the whole content of the table as a histogram
// For each bucket, print a '*' to indicate an item
void printAsHistogram(struct HashTable* ht);
#endif //TP15_2_HASHISH_HASHTABLEINTLIST_H
