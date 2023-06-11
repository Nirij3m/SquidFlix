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
    h1->table = malloc(buckets*sizeof(struct ListDirector*));

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
    unsigned long hash = 5381;
    int c;

    while (c = *director++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash%ht->buckets;
}

bool insert(struct HashTable* ht, char* director, char* title, int duration, char* genre, int* maxFilm){
    if(isHashTableEmpty(ht)){
        return false;
    }
    int hashedValue = hash_function(ht, director);
    if(ht->table[hashedValue] == NULL){ //vide, créer la liste et insérer la valeur

        ht->table[hashedValue] = createEmptyListDirector();
        addFirstDirector(ht->table[hashedValue], director); //j'ajoute le directeur en début de liste
        addFirstFilm(ht->table[hashedValue]->head->films, title, duration, genre); //j'ajoute le film du directeur situé en début de list
        ht->table[hashedValue]->head->nmbFilm++; //J'incrémente le nombre de film

        if(ht->table[hashedValue]->head->nmbFilm > *maxFilm){ //Ce directeur à fait le plus de film, je stocke sa cellule comme topDirector
            ht->topDirector = ht->table[hashedValue]->head;
        }
        ht->items++;
        return true;

    }
    else{ //il y a collision, j'ajoute à la liste la valeur
        struct Director* temp = directorBelongs(ht->table[hashedValue],director); //DirectorBelongs return the cell if founded or NULL if not

        if(temp != NULL){ //Le directeur existe déjà
            temp->nmbFilm++;
            addFirstFilm(temp->films, title, duration, genre);

            if(temp->nmbFilm > *maxFilm){ //Ce directeur à fait le plus de film, je stocke sa cellule comme topDirector
                ht->topDirector = temp;
            }
            return true;
        }
        else { //Il y a collision mais le directeur n'appartient pas

            addFirstDirector(ht->table[hashedValue], director);
            addFirstFilm(ht->table[hashedValue]->head->films, title, duration, genre);
            ht->table[hashedValue]->head->nmbFilm++;

            if(ht->table[hashedValue]->head->nmbFilm > *maxFilm){ //Ce directeur à fait le plus de film, je stocke sa cellule comme topDirector
                ht->topDirector = ht->table[hashedValue]->head;
            }
            return true;
        }
    }
    return false;
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
        else printListDirector(ht->table[i]);

    }
}

bool exists(struct HashTable* ht, char* director){
    int hash = hash_function(ht, director);
    if(ht->table[hash] == NULL){
        return false;
    }
    else return true;
}

void deleteItem(struct HashTable* ht, char* director){
    if(isHashTableEmpty(ht)){
        printf("HT empty maaan");
        return;
    }
    int hashedValue = hash_function(ht, director);
    bool valid = true;
    if(exists(ht, director)){

        if(ht->table[hashedValue]->size > 1){ //Il y a plusieurs collisions, il faut parcourir la liste des collisions
            int posValue = getPosItemDirector(ht->table[hashedValue], director); //Obtient la position de l'élement à supprimer dans la liste
            deleteItemPosDirector(ht->table[hashedValue], posValue, &valid);// Supprimer l'élement à la position renseignée
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
        deleteListDirector(&(*ht)->table[i]);
    }
    free((*ht)->table);
    free(*ht);
    ht = NULL;
}

