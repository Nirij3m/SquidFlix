//
// Created by nirin on 5/12/2023.
//

#include "hashTableDirectorList.h"

struct HashTable* createEmptyHashTable(unsigned int buckets){
    struct HashTable* h1 = malloc(sizeof(struct HashTable));
    if(h1 == NULL){
        printf("malloc error");
        return h1;
    }
    h1->buckets = buckets;
    h1->items = 0;
    h1->table = malloc(buckets*sizeof(struct ListFilm));
}
bool isHashTableEmpty(struct HashTable* ht){
    if(ht == NULL){
        return true;
    }
    else return false;
}

unsigned int hashTableElements(struct HashTable* ht){
    if(isHashTableEmpty(ht)){
        return 0;
    }
    return ht->items;
    
}

int hash_function(struct HashTable* ht, char* director){
    if(isHashTableEmpty(ht)){
        printf("HT Empty");
        return 0;
    }
    int result = 0;
    for(int i = 0; i < strlen(director); i++){
        result += director[i];
    }
    return result%ht->buckets;
}

bool insert(struct HashTable* ht, int value){
    if(isHashTableEmpty(ht)){
        return false;
    }
    int hashedValue = hash_function(ht, char* director);
    if(ht->table[hashedValue] == NULL){ //vide, créer la liste et insérer la valeur

        ht->table[hashedValue] = createEmptyListFilm();
        addFirst(ht->table[hashedValue], value);
        ht->items++;
        return true;

    }
    else{ //il y a collision, j'ajoute à la liste la valeur
        addFirst(ht->table[hashedValue], value);
        ht->items++;
        return true;
    }
}

bool exists(struct HashTable* ht, int value){
    if(isHashTableEmpty(ht)){
        return false;
    }

    int hashedValue = hash_function(ht, value);
    if(ht->table[hashedValue] == NULL){
        return false;
    }
    else{
        if(belongs(ht->table[hashedValue], value) == ht->table[hashedValue]->head){
            return false;
        } //belongs retourne la tête de liste => élément pas retrouvé
        else return true;
    }
}

void printHashTable(struct HashTable* ht){
    if(isHashTableEmpty(ht)){
        printf("HashTable Empty");
        return;
    }
    for(int i = 0; i < ht->buckets; i++){
        printf("%d: ", i);
        if(ht->table[i] == NULL){
            printf("\n");
        }
        else printList(ht->table[i]);

    }
}

void deleteItem(struct HashTable* ht, int value){
    if(isHashTableEmpty(ht)){
        printf("HT empty maaan");
        return;
    }
    int hashedValue = hash_function(ht, value);
    bool valid = true;
    if(exists(ht, value)){

        if(ht->table[hashedValue]->size > 1){ //Il y a plusieurs collisions, il faut parcourir la liste des collisions
            int posValue = getPosItem(ht->table[hashedValue], value); //Obtient la position de l'élement à supprimer dans la liste
            deleteItemPos(ht->table[hashedValue], posValue, &valid);// Supprimer l'élement à la position renseignée
        }
        //Finir la suppression

    }
}

void deleteHashTable(struct HashTable** ht){
    if(isHashTableEmpty(*ht)){
        printf("HT empty");
        return;
    }

    for(int i = 0; i < (*ht)->buckets; i++){
        deleteList(&(*ht)->table[i]);
    }
    free((*ht)->table);
    free(*ht);
    ht = NULL;
}

void printAsHistogram(struct HashTable* ht){
    if(isHashTableEmpty(ht)){
        printf("HT Empty");
        return;
    }

    for(int i = 0; i < ht->buckets; i++){
        printf("%d: ");
        for(int j = 0; j < ht->table[i]->size; j++){
            printf("*");
        }
        printf("\n");
    }
}