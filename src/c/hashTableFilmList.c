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

int hash_functionFilm(struct HashTableFilm* ht, char* title){
    unsigned long hash = 5381;
    int c;

    while (c = *title++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash%ht->buckets;
}

int hash_functionGenre(struct HashTableFilm* ht, char* genre){
    return genre[0];
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
    else { //Il y a collision
        addFirstFilm(ht->table[hashedValue], title, duration, genre);
        return true;
    }
    return false;
}

bool insertFilmGenre(struct HashTableFilm* ht, char* genre, int duration, char* title){ //Fonction insertion pour le genre
    if(isHashTableEmptyFilm(ht)){
        return false;
    }
    int hashedValue = hash_functionGenre(ht, genre);
    if(ht->table[hashedValue] == NULL){ //vide, créer la liste et insérer la valeur

        ht->table[hashedValue] = createEmptyListFilm();
        addFirstFilm(ht->table[hashedValue], title, duration, genre);
        ht->items++;
        return true;

    }
    else { //Il y a collision, je dois ajouter le film de manière triée, il n'y a pas de mélange de genre ayant le même hash
        struct CellFilm* iter = ht->table[hashedValue]->head;
        int pos = 0;
        while(strcmp(iter->genre, genre) != 0 && iter->next != NULL){ //Je cherche la première occurence du genre
            iter = iter->next;
            pos++;
        }
        if(pos == 0){ //La genre recherché est au début de la liste
            addFirstFilm(ht->table[hashedValue], title, duration, genre);
        }
        else{ //Le genre recherché est à la position "pos" dans la liste
            bool valid = true;
            addItemPosFilm(ht->table[hashedValue], title, duration, genre, pos, &valid);
        }
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

