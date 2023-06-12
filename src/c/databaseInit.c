#include "databaseInit.h"
#include<unistd.h>

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
    int maxFilm = 0;
    while(!feof(file)){
        fscanf(file, "%[^;];%[^;];%d;%[^\n]\n", director, title, &duration, genre); //Lis les champs avec comme séparateur le point virgule
        genre[strcspn(genre, "\r")] = '\0';
        insert(ht, director, title, duration, genre, &maxFilm);
        insertFilm(timeArray, title, duration, genre);
        insertFilmGenre(genreTable, genre, duration, title); //Table de Hashage selon le genre
        insertFilmRead(filmTable, title, duration, genre); //Table de Hachage selon le titre du film
    }
    fclose(file);
    return ht;
}

void findByDirector(char* director, struct HashTable* ht, char* destination){
    double time_spent = 0.0;
    clock_t begin = clock();

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
        fprintf(result, "%s\n", destination);
        fprintf(result, "NULL");
        fclose(result);
        ready = fopen("ready.txt", "w");
        fclose(ready);
        return;
    }
    else{ //Je vais itérer sur toute la liste du director
        struct CellFilm* iter = d->films->head;
        int listSize = listSizeFilm(d->films);

        clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        fprintf(result, "%s\n", destination);
        fprintf(result, "%f", time_spent); //j'insère le temps de la fonction //j'insère le temps de la fonction
        for(int i = 0; i < listSize; i++){
            fprintf(result, "\n%s;%d;%s", iter->nomFilm, iter->duration, iter->genre); //je rajoute les champs séparés par des ";"
            iter = iter->next;
        }
    }
    fclose(result);
    ready = fopen("ready.txt", "w"); //Création du fichier prêt pour lecture du côté front end;
    fclose(ready);


}

void findByDuration(int duration, struct ListFilm** timeArray, char* destination){
    double time_spent = 0.0;
    clock_t begin = clock();

    FILE* ready;
    FILE* result;
    result = fopen("results.txt", "w");


    if(duration > 500 || duration < 0 || timeArray[duration] == NULL){
        fprintf(result, "%s\n", destination);
        fprintf(result, "NULL");
        fclose(result);
        ready = fopen("ready.txt", "w");
        fclose(ready);
        return;
    }
    else{
        struct CellFilm* iter = timeArray[duration]->head;
        int listSize = listSizeFilm(timeArray[duration]);

        clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        fprintf(result, "%s\n", destination);
        fprintf(result, "%f", time_spent); //j'insère le temps de la fonction //j'insère le temps de la fonction
        for(int i = 0; i < listSize; i++){
            fprintf(result, "\n%s;%d;%s", iter->nomFilm, iter->duration, iter->genre); //je rajoute les champs séparés par des ";"

            iter = iter->next;
        }
    }
    fclose(result);
    ready = fopen("ready.txt", "w");
    fclose(ready);


}

void findByGenre(char* genre, struct HashTableFilm* genres, char* destination){
    double time_spent = 0.0;
    clock_t begin = clock();

    int hashedValue = hash_functionGenre(genres, genre);

    FILE* ready;
    FILE* result;
    result = fopen("results.txt", "w");

    if(hashedValue > 130 || hashedValue < 0 || isListEmptyFilm(genres->table[hashedValue])){ //Le genre rentrée n'est pas connu dans la base de donnée
        fprintf(result, "%s\n", destination);
        fprintf(result, "NULL");
        fclose(result);
        ready = fopen("ready.txt", "w");
        fclose(ready);
        return;
    }

    struct CellFilm* iter = genres->table[hashedValue]->head;
    while(strcmp(iter->genre, genre) != 0){ //Je vais au buckets, s'il y a des collisions je me déplace jusqu'à avoir le bon genre
        iter = iter->next;
    }

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(result, "%s\n", destination);
    fprintf(result, "%f", time_spent); //j'insère le temps de la fonction

    while(iter != NULL && strcmp(iter->genre, genre) == 0) { //Je parcours la différence restante de la liste
        fprintf(result, "\n%s;%d;%s", iter->nomFilm, iter->duration, iter->genre);
        iter = iter->next;
    }

    fclose(result);
    ready = fopen("ready.txt", "w");
    fclose(ready);

}

void randomFilm(struct HashTableFilm* films, char* destination){
    double time_spent = 0.0;
    clock_t begin = clock();
    srand(time(NULL));
    int r = 0;

    FILE* result;
    FILE* ready;
    result = fopen("res_random.txt", "w");

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(result, "%s\n", destination);
    fprintf(result, "%f", time_spent); //j'insère le temps de la fonction

    for(int i =0; i < 4; i++){ //Je génère 4 films aléatoire

        r = rand()%films->buckets;
        fprintf(result, "\n%s;%d;%s", films->table[r]->head->genre, films->table[r]->head->duration, films->table[r]->head->nomFilm); //J'ajoute depuis des positions 4 films;
    }
    fclose(result);
    ready = fopen("ready1.txt", "w"); //Création du fichier prêt pour lecture du côté front end;
    fclose(ready);

}

void allDirectors(struct HashTable* dir, char* destination){
    double time_spent = 0.0;
    clock_t begin = clock();

    int size = dir->buckets;
    FILE* result;
    FILE* ready;
    result = fopen("res_allDirector.txt", "w");

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(result, "%s\n", destination);
    fprintf(result, "%f", time_spent); //j'insère le temps de la fonction

    struct Director* iter;
    for(int i = 0; i < size; i++) { //Je parcours tous les buckets

        if (!isListEmptyDirector(dir->table[i])) {
            int listSize = listSizeDirector(dir->table[i]);
            iter = dir->table[i]->head;

            for (int j = 0;
                 j < listSize; j++); //A chaque bucket je parcours le list associée et je print le nom du directeur

                 fprintf(result, "\n%s", iter->name);
            iter = iter->next;
        }
    }

    fclose(result);
    ready = fopen("ready2.txt", "w"); //Création du fichier prêt pour lecture du côté front end;
    fclose(ready);
}

void printTopDirector(struct HashTable* dir, char* destination){
    double time_spent = 0.0;
    clock_t begin = clock();

    FILE* result;
    FILE* ready;

    result = fopen("res_director.txt", "w");
    struct Director* topD = topDirector(dir);

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(result, "%s\n", destination);
    fprintf(result, "%f", time_spent); //j'insère le temps de la fonction

    fprintf(result, "\n%s;%d", topD->name, topD->nmbFilm);

    fclose(result);
    ready = fopen("ready0.txt", "w"); //Création du fichier prêt pour lecture du côté front end;
    fclose(ready);
}

void clearInput(){

    usleep(10000000);
    remove("results.txt");
    remove("ready.txt");
}