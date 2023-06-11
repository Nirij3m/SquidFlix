//
// Created by nirin on 5/12/2023.
//

#include "hashTableFilmList.h"


struct HashTableFilm* createEmptyHashTableFilm(unsigned int buckets){
    struct HashTableFilm* h1 = malloc(sizeof(struct HashTableFilm));
    if(h1 == NULL){
        printf("malloc error");
        return h1;
    }
    h1->buckets = buckets;
    h1->items = 0;
    h1->table = malloc(buckets*sizeof(struct ListFilm*));

}
bool isHashTableEmptyFilm(struct HashTableFilm* ht){
    if(ht == NULL){
        return true;
    }
    else return false;
}

unsigned int hashTableElementsFilm(struct HashTableFilm* ht){
    if(isHashTableEmptyFilm(ht)){
        return 0;
    }
    return ht->items;
    
}

int hash_functionFilm(struct HashTableFilm* ht, char* genre){
    unsigned long hash = 5381;
    int c;

    while (c = *genre++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash%ht->buckets;
}

bool insertFilmRead(struct HashTableFilm* ht, char* title, int duration, char* genre){
    if(isHashTableEmptyFilm(ht)){
        return false;
    }
    int hashedValue = hash_functionFilm(ht, genre);
    if(ht->table[hashedValue] == NULL){ //vide, créer la liste et insérer la valeur

        ht->table[hashedValue] = createEmptyListFilm();
        addFirstFilm(ht->table[hashedValue], title, duration, genre);
        ht->items++;
        return true;

    }
    else { //Il y a collision mais le directeur n'appartient pas
        addFirstFilm(ht->table[hashedValue], title, duration, genre);
        return true;
    }
    return false;
}



void printHashTableFilm(struct HashTableFilm* ht){
    if(isHashTableEmptyFilm(ht)){
        printf("HashTable Empty");
        return;
    }
    for(int i = 0; i < ht->buckets; i++){
        printf("%d: ", i);
        if(ht->table[i] == NULL){
            printf("\n");
        }
        else printListFilm(ht->table[i]);

    }
}

bool existsFilm(struct HashTableFilm* ht, char* genre){
    int hash = hash_functionFilm(ht, genre);
    if(ht->table[hash] == NULL){
        return false;
    }
    else return true;
}



void deleteHashTableFilm(struct HashTableFilm** ht){
    if(isHashTableEmptyFilm(*ht)){
        printf("HT empty");
        return;
    }

    for(int i = 0; i < (*ht)->buckets; i++){
        deleteListFilm(&(*ht)->table[i]);
    }
    free((*ht)->table);
    free(*ht);
    ht = NULL;
}

