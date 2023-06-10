#include "databaseInit.h"

struct HashTable* readDirectors(char* fileName){
    struct HashTable* ht = createEmptyHashTable(2500);
    struct HashTable* filmType = createEmptyHashTable(100);
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        printf("File unreadeable");
        return NULL;
    }

    char director[256];
    char title[256];
    int duration;
    char genre[256];
    while(!feof(file)){
        fscanf(file, "%[^;];%[^;];%d;%[^\n]\n", director, title, &duration, genre);
        genre[strcspn(genre, "\r")] = '\0';
        insert(ht, director, title, duration, genre);
        insert(filmType, )
    }
    fclose(file);
    return ht;

}
