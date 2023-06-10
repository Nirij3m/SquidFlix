#include "databaseInit.h"

struct HashTable* readDirectors(char* fileName, struct ListFilm** timeArray, struct HashTableFilm* genreTable, struct HashTableFilm* filmTable){

    struct HashTable* ht = createEmptyHashTable(2500);

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
        insertFilm(timeArray, title, duration, genre);
        insertFilmRead(genreTable, title, duration, genre);
        insertFilmRead(filmTable, genre, duration, title);
    }
    fclose(file);
    return ht;
}

void findByDirector(char* director){
    struct HashTable* ht = readDirectors("BD_medium.txt", NULL, NULL, NULL);
    bool exist = NULL;
    int hashedValue = hash_function(ht, director);
    struct Director* d = directorBelongs(ht->table[hashedValue], director);

    if(d == NULL){ //Retour NULL donc n'exist pas, l'entrée utilisateur n'est pas bonne
        exist = false;
    }
    else exist = true;


    //Création du fichier results
    FILE* result;
    FILE* ready;
    result = fopen("results.txt", "w");
    if(!exist){ //Directeur inexistant, je renvoie NULL
        fprintf(result, "NULL");
        fclose(result);
        return;
    }
    else{ //Je vais itérer sur toute la liste du director
        struct CellFilm* iter = d->films->head;
        int listSize = listSizeFilm(d->films);
        fprintf(result, "%d", 0); //j'insère le temps de la fonction
        for(int i = 0; i < listSize; i++){
            fprintf(result, "%d", 0);
            fprintf(result, "\n%s;%d;%s", iter->nomFilm, iter->duration, iter->genre); //je rajoute les champs séparés par des ";"
            iter = iter->next;
        }
    }
    fclose(result);
    ready = fopen("ready.txt", "w"); //Création du fichier prêt pour lecture du côté front end;
    fclose(ready);
    deleteHashTable(&ht);

}

void findByDuration(int duration){
    struct ListFilm** timeArray = createTimeArray();
    struct HashTable* ht = readDirectors("BD_medium.txt", timeArray, NULL, NULL);
    FILE* ready;
    FILE* result;
    result = fopen("results.txt", "w");


    if(duration > 500 || duration < 0){
        fscanf(result, "NULL");
        fclose(result);
        return;
    }
    else{
        struct CellFilm* iter = timeArray[duration]->head;
        int listSize = listSizeFilm(timeArray[duration]);
        fprintf(result, "%d", 0); //j'insère le temps de la fonction
        for(int i = 0; i < listSize; i++){
            fprintf(result, "\n%s;%d;%s", iter->nomFilm, iter->duration, iter->genre); //je rajoute les champs séparés par des ";"

            iter = iter->next;
        }
    }
    fclose(result);
    ready = fopen("ready.txt", "w");
    fclose(ready);

    freeTimeArray(timeArray);
    deleteHashTable(&ht);

}

void randomFilm(){
    srand(time(NULL));
    int r = 0;
    struct HashTableFilm* films = createEmptyHashTableFilm(1000);
    readDirectors("BD_medium.txt", NULL, NULL, NULL);
    FILE* result;
    FILE* ready;
    result = fopen("results.txt", "w");
    fprintf(result, "%d", 0);
    for(int i =0; i < 4; i++){ //Je génère 4 films aléatoire

        r = rand()%films->buckets;
        fprintf(result, "\n%s;%d;%s", films->table[r]->head->genre, films->table[r]->head->duration, films->table[r]->head->nomFilm); //J'ajoute depuis des positions 4 films;
    }
    fclose(result);
    ready = fopen("ready.txt", "w"); //Création du fichier prêt pour lecture du côté front end;
    fclose(ready);

    deleteHashTableFilm(&films);

}



