#include "listDirector.h"

struct Director* createCellDirector(char* name){
    struct Director* d = malloc(sizeof(struct Director));
    if(d != NULL){
        d->name = malloc(sizeof(char)*(strlen(name) + 1));
        strcpy(d->name, name);

        d->nmbFilm = 0;

        d->films = malloc(50*sizeof(struct ListFilm*)); //Par défaut, une réalisateur à 50 films par défaut
    }
    return d;
}
struct ListDirector* createEmptyListDirector(){

    struct ListDirector* l1 = malloc(sizeof(struct ListDirector));
    if(l1==NULL){
        printf("malloc error");
        return l1;
    }
    l1->size = 0;
    l1->head = NULL;

    return l1;
}

void addFirstDirector(struct ListDirector* l, char* name){
    struct Director* newLHead = createCellDirector(name);
    if(newLHead==NULL){
        printf("head malloc error");
    }

    newLHead -> next = l->head;
    l->head = newLHead;
    l->size++;
}

bool isListEmptyDirector(struct ListDirector* l){
    if(l == NULL){
    return true;
    }
    else return false;
}


struct Director* getItemPosDirector(struct ListDirector* l, unsigned int position, bool* valid){
    //here, the position in the exact index of the cell in the lise. No need of -1 position
    if(isListEmptyDirector(l)){
        printf("list empty");
        *valid = false;
        return NULL;
    }

    if(position >= l->size){
        *valid = false;
    }

    int i = 0;
    struct Director* iter = l->head;
    while(i <= position-1){
        iter = iter->next;
        i++;
    }
    *valid = true;
    return iter;
}


void deleteFirstDirector(struct ListDirector* l){

    if (!isListEmptyDirector(l)) {
        struct Director* newHead = l->head->next;
        deleteListFilm(&l->head->films);
        free(l->head->name);
        free(l->head);
        l->head = newHead;
        l->size--;
        return;
    }
}

void printListDirector(struct ListDirector* l){

    if(isListEmptyDirector(l)){
        printf("List is empty :(\n");
        return;
    }

    unsigned int size = l->size;
    struct Director* iter = l->head;

    for(int i = 0; i < size; i++){
        printf(" -> ");
        printf("Director: %s - NumberFilm: %d", iter->name, iter->nmbFilm);
        iter = iter->next;
    }
    printf("\n");
}

unsigned int listSizeDirector(struct ListDirector* l){
    return l->size;
}

void addItemPosDirector(struct ListDirector* l, char* name, unsigned int position, bool* valid){

    unsigned int size = listSizeDirector(l);

    if(position > size){
        printf("List empty :( or out of range");
        *valid = false;
        return;
    }

    if(position==0){
        addFirstDirector(l, name);
        if(size == listSizeDirector(l)){
            *valid = false;
            return;
        } //même taille, addFrist n'a pas marché
        else{
            *valid = true;
            return;
        }
    }

    struct Director* newCell = createCellDirector(name); //je créer la cellule a ajouter
    if(newCell == NULL){
        printf("Malloc Error !");
        *valid = false;
        return;

    }

    struct Director* iter = l->head;
    int i = 0;
    while(i < position-1){ // se décale juqsu'à pos-1
        if(iter == NULL){
            printf("Hole in the list !");
            *valid = false;
            return;
        }
        iter = iter->next;
        i++;
    }
    //connecte nouvelle cellule et pos
    newCell -> next = iter -> next;
    iter -> next = newCell;
    l->size++;
    *valid = true;

}

void deleteItemPosDirector(struct ListDirector* l, unsigned int position, bool* valid){

    if(isListEmptyDirector(l) || position > listSizeDirector(l)){
        printf("Error, list empty or position out of range");
        *valid = false;
        return;
    }

    if(position == 0){ //if you want to delete the head
        return deleteFirstDirector(l);
    }

    struct Director* iter = l->head;
    int i = 0;
    while(i < position-1) {
        iter = iter -> next;
        i++;
    }

    struct Director* temp = iter -> next; // enregistre le pont à pos-1
    iter->next = iter->next->next;
    l->size--;
    *valid = true;

    //free the array deleted form the list
    free(temp);

}

void deleteListDirector(struct ListDirector** l){

        if(isListEmptyDirector(*l)){
            free(*l);
            return;
        }
        unsigned int size = listSizeDirector(*l);
        for(int i = 0; i < size; i++){
            deleteFirstDirector(*l);
        }

        free(*l);
        *l = NULL;
}


struct Director* directorBelongs(struct ListDirector* l, char* name){
    if(isListEmptyDirector(l)){
        printf("List empty man");
        return NULL;
    }

    unsigned int size = listSizeDirector(l);
    struct Director* iter = l->head;

    for(int i = 0; i < size; i++){
        if(strcmp(iter->name, name) == 0){
            return iter;
        }
        else{
            iter = iter->next;
        }
    }// rien n'est trouvé
    return NULL;
}

struct Director* topDirector(struct ListDirector* ld){
    return ld->topDirector;
}



int getPosItemDirector(struct ListDirector* l, char* name){
    if(isListEmptyDirector(l)){
        printf("list empty");
        return 0;
    }

    int i = 0;
    struct Director* iter = l->head;
    while(strcmp(iter->name, name) != 0){
        iter = iter->next;
        i++;
    }
    return i;
}




