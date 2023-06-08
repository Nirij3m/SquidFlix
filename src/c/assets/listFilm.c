#include "listFilm.h"


struct CellFilm* createCellFilm(char* nomFilm, int duration, char* genre){
    struct CellFilm* c = malloc(sizeof(struct CellFilm));
    if(c == NULL){
        printf("Cell commited sepuku");
    }
    c -> nomFilm = malloc(sizeof(char)*(strlen(nomFilm)+1));
    strcpy(c->nomFilm, nomFilm);

    c -> duration = duration;

    c-> genre = malloc(sizeof(char)*(strlen(genre)+1));
    strcpy(c->genre, genre);

    c -> next = NULL;

    return c;

}

bool isListEmpty(struct ListFilm* l){
    if(l == NULL){
        return true;
    }
    else return false;
}

unsigned int listSize(struct ListFilm* l){
    return l->size;
}



struct ListFilm* createEmptyListFilm(){

    struct ListFilm* l1 = malloc(sizeof(struct ListFilm));
    if(l1==NULL){
        printf("malloc error");
        return l1;
    }
    l1->size = 0;
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


struct CellFilm* getItemPosFilm(struct ListFilm* l, unsigned int position, bool* valid){
    //here, the position in the exact index of the cell in the lise. No need of -1 position
    if(isListEmpty(l)){
        printf("list empty");
        *valid = false;
        return NULL;
    }

    if(position >= l->size){
        *valid = false;
    }

    int i = 0;
    struct CellFilm* iter = l->head;
    while(i <= position-1){
        iter = iter->next;
        i++;
    }
    *valid = true;
    return iter;
}


void deleteFirstFilm(struct ListFilm* l){

    if (!isListEmpty(l)) {
        struct CellFilm* newHead = l->head->next;
        free(l->head->nomFilm);
        free(l->head->genre);
        free(l->head);
        l->head = newHead;
        l->size--;
        return;
    }
}

void printListFilm(struct ListFilm* l){

    if(isListEmpty(l)){
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

void addItemPosFilm(struct ListFilm* l, char* nomFilm, int duration, char* genre, unsigned int position, bool* valid){

    unsigned int size = listSize(l);

    if(position > size){
        printf("List empty :( or out of range");
        *valid = false;
        return;
    }

    if(position==0){
        addFirstFilm(l, nomFilm, duration, genre);
        if(size == listSize(l)){
            *valid = false;
            return;
        } //même taille, addFrist n'a pas marché
        else{
            *valid = true;
            return;
        }
    }

    struct CellFilm* newCell = createCellFilm(nomFilm, duration, genre); //je créer la cellule a ajouter
    if(newCell == NULL){
        printf("Malloc Error !");
        *valid = false;
        return;

    }

    struct CellFilm* iter = l->head;
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

void deleteItemPosFilm(struct ListFilm* l, unsigned int position, bool* valid){

    if(isListEmpty(l) || position > listSize(l)){
        printf("Error, list empty or position out of range");
        *valid = false;
        return;
    }

    if(position == 0){ //if you want to delete the head
        return deleteFirstFilm(l);
    }

    struct CellFilm* iter = l->head;
    int i = 0;
    while(i < position-1) {
        iter = iter -> next;
        i++;
    }

    struct CellFilm* temp = iter -> next; // enregistre le pont à pos-1
    iter->next = iter->next->next;
    l->size--;
    *valid = true;

    //free the array deleted form the list
    free(temp);

}

void deleteListFilm(struct ListFilm** l){

        if(isListEmpty(*l)){
            free(*l);
            return;
        }
        unsigned int size = listSize(*l);
        for(int i = 0; i < size; i++){
            deleteFirstFilm(*l);
        }

        free(*l);
        *l = NULL;
}

struct CellFilm* filmBelongs(struct ListFilm* l, char* nomFilm, int duration, char* genre){
    if(isListEmpty(l)){
        printf("List empty man");
        return l->head;
    }

    unsigned int size = listSize(l);
    struct CellFilm* iter = l->head;

    for(int i = 0; i < size; i++){
        if(strcmp(iter->nomFilm, nomFilm) == 0 && strcmp(iter->genre, genre) == 0 && iter->duration == duration){
            return iter;
        }
        else{
            iter = iter->next;
        }
    }
    return l->head;
}


/*int getPosItem(struct ListFilm* l, int value){
    if(isListEmpty(l)){
        printf("list empty");
        return l->size;
    }

    int i = 0;
    struct CellFilm* iter = l->head;
    while(iter->value != value){
        iter = iter->next;
        i++;
    }
    return i;
}
 */
