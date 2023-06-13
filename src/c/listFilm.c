#include "listFilm.h"


struct CellFilm* createCellFilm(char* nomFilm, int duration, char* genre){
    struct CellFilm* c = malloc(sizeof(struct CellFilm));
    if(c == NULL){
        printf("Cell commited sepuku");
        return c;
    }
    c -> nomFilm = malloc(sizeof(char)*(strlen(nomFilm)+1));
    strcpy(c->nomFilm, nomFilm);

    c -> duration = duration;

    c-> genre = malloc(sizeof(char)*(strlen(genre)+1));
    strcpy(c->genre, genre);

    c -> next = NULL;

    return c;

}

struct Director* createDirector(char* name){
    struct Director* d = malloc(sizeof(struct Director));
    d->name = malloc((strlen(name)+1)*sizeof(char));
    d->nmbFilm = 0;
}

bool isListEmptyFilm(struct ListFilm* l){
    if(l == NULL){
        return true;
    }
    else return false;
}

unsigned int listSizeFilm(struct ListFilm* l){
    return l->size;
}



struct ListFilm* createEmptyListFilm(){

    struct ListFilm* l1 = malloc(sizeof(struct ListFilm));
    if(l1==NULL){
        printf("malloc error");
        return l1;
    }
    l1->size = 0;
    l1->director = NULL;
    l1->head = NULL;

    return l1;
}

void addFirstFilm(struct ListFilm* l, char* nomFilm, int duration, char* genre){
    struct CellFilm* newLHead = createCellFilm(nomFilm, duration, genre);
    if(newLHead==NULL){
        printf("head malloc error");
    }

    newLHead -> next = l->head;
    l->head = newLHead;
    l->size++;

}


void deleteFirstFilm(struct ListFilm* l){

    if (!isListEmptyFilm(l)) {
        struct CellFilm* newHead = l->head->next;
        free(l->head->nomFilm);
        l->head->nomFilm = NULL;
        free(l->head->genre);
        l->head->genre = NULL;
        free(l->head);
        l->head = NULL;
        l->head = newHead;
        l->size--;
        return;
    }
}

void printListFilm(struct ListFilm* l){

    if(isListEmptyFilm(l)){
        printf("List is empty :(\n");
        return;
    }

    unsigned int size = l->size;
    struct CellFilm* iter = l->head;

    for(int i = 0; i < size; i++){
        printf(" -> ");
        printf("Nom film: %s - Durée: %d - Genre: %s\n", iter->nomFilm, iter->duration, iter->genre);

        iter = iter->next;
    }
    printf("\n");
}

void deleteDirector(struct Director* d){
    free(d->name);
}


void deleteListFilm(struct ListFilm** l){

        if(isListEmptyFilm(*l)){
            free((*l)->director);
            free(*l);
            *l = NULL;
            return;
        }
        unsigned int size = listSizeFilm(*l);
        for(int i = 0; i < size; i++){
            deleteFirstFilm(*l);
        }

        if((*l)->director != NULL){ //delete director of the list
            free((*l)->director);
            (*l)->director = NULL;
        }

        free(*l);
        *l = NULL;
}

struct ListFilm** createTimeArray(){
    struct ListFilm** timeArray = malloc(500*sizeof(struct ListFilm*));
    for(int i =0; i < 500; i++){
        timeArray[i] = malloc(sizeof(struct ListFilm));

    }
    return timeArray;
}

bool insertFilm(struct ListFilm** timeArray, char* title, int duration, char* genre){
    if(isListEmptyFilm(*timeArray)){
        return false;
    }
    if(timeArray[duration] == NULL){
        timeArray[duration] = createEmptyListFilm();
        addFirstFilm(timeArray[duration], title, duration, genre);
    }
    else{
        addFirstFilm(timeArray[duration],title, duration, genre);
    }

}

void freeTimeArray(struct ListFilm** timeArray){

    for(int i = 0; i < 500; i++){
        deleteListFilm(&timeArray[i]);
        free(timeArray[i]);
    }
    free(timeArray);
    timeArray = NULL;
}

void printTimeArray(struct ListFilm** timeArray){
    for(int i = 0; i < 500; i++) {
        if (timeArray[i] != NULL) {
            printf("%d: ", i);
            printListFilm(timeArray[i]);
        }
        else printf("NONE");
    }
}


