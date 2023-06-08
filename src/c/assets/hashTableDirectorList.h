//
// Created by nirin on 5/12/2023.
//

#ifndef TP15_2_HASHISH_HASHTABLEINTLIST_H

#include "listFilm.h"
#include "../film.h"
#include <time.h>
#define TP15_2_HASHISH_HASHTABLEINTLIST_H

struct HashTable {
    unsigned int items;
    unsigned int buckets;
    struct ListFilm** table;
};

struct HashTable* createEmptyHashTable(unsigned int buckets);
bool isHashTableEmpty(struct HashTable* ht);
unsigned int hashTableElements(struct HashTable* ht);
int hash_function(struct HashTable* ht, char* name);
// Inserts "value" in the table. If no collision, it returns True, otherwise False
bool insert(struct HashTable* ht, struct Director*);
bool exists(struct HashTable* ht, struct Director*);
void printHashTable(struct HashTable* ht);
void deleteItem(struct HashTable* ht, struct Director*);
void deleteHashTable(struct HashTable** ht);

#endif //TP15_2_HASHISH_HASHTABLEINTLIST_H
