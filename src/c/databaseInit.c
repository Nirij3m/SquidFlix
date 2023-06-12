#include "databaseInit.h"
#include<unistd.h>



void findByDirector(char* director, struct NodeTrie* trie, char* destination){
    double time_spent = 0.0;
    clock_t begin = clock();


    bool exist = NULL;
    char preword[32];
    memset(preword, '\0', 32);
    struct ListFilm* films = findDirector(trie, preword, director, 0);

    if(films == NULL){ //Retour NULL donc n'exist pas, l'entrée utilisateur n'est pas bonne
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
        struct CellFilm* iter = films->head;
        int listSize = listSizeFilm(films);

        clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        fprintf(result, "%s\n", destination);
        fprintf(result, "%f", time_spent); //j'insère le temps de la fonction //j'insère le temps de la fonction
        for(int i = 0; i < listSize; i++){
            fprintf(result, "\n%s;%s;%d;%s", films->director,iter->nomFilm, iter->duration, iter->genre); //je rajoute les champs séparés par des ";"
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

void findByGenre(char* genre, struct NodeTrie* genres, char* destination){
    double time_spent = 0.0;
    clock_t begin = clock();

    bool exist = NULL;
    char preword[32];
    memset(preword, '\0', 32);
    struct ListFilm* films = findDirector(genres, preword, genre, 0);

    if(films == NULL){ //Retour NULL donc n'exist pas, l'entrée utilisateur n'est pas bonne
        exist = false;
    }
    else exist = true;

    FILE* ready;
    FILE* result;
    result = fopen("results.txt", "w");

    if(!exist){ //genre inexistant
        fprintf(result, "%s\n", destination);
        fprintf(result, "NULL");
        fclose(result);
        ready = fopen("ready.txt", "w");
        fclose(ready);
        return;
    }
    else{ //Je vais itérer sur toute la liste du genre
        struct CellFilm* iter = films->head;
        int listSize = listSizeFilm(films);

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

void randomFilm(struct ListFilm** timeArray, char* destination){
    double time_spent = 0.0;
    clock_t begin = clock();
    srand(time(NULL));
    int pos = 0;
    int size = 0;

    FILE* result;
    FILE* ready;
    result = fopen("res_random.txt", "w");

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(result, "%s\n", destination);
    fprintf(result, "%f", time_spent); //j'insère le temps de la fonction
    for(int i = 0; i < 4; i++){
            pos = (100+rand())%500;
        while(timeArray[pos]->head == NULL){ // Je veux une position non vide
            pos = (100+rand())%500;
        }

        struct CellFilm* iter = timeArray[pos]->head;
        fprintf(result, "\n%s;%d;%s", iter->nomFilm, iter->duration, iter->genre);
    }


    fclose(result);
    ready = fopen("ready1.txt", "w"); //Création du fichier prêt pour lecture du côté front end;
    fclose(ready);

}

void allDirectors(struct NodeTrie* trie, char* destination){
    double time_spent = 0.0;
    clock_t begin = clock();

    FILE* result;
    FILE* ready;
    result = fopen("res_allDirector.txt", "w");

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(result, "%s\n", destination);
    fprintf(result, "%f", time_spent); //j'insère le temps de la fonction

    preorderDirector(trie, result);

    fclose(result);
    ready = fopen("ready2.txt", "w"); //Création du fichier prêt pour lecture du côté front end;
    fclose(ready);
}

void allFilms(struct NodeTrie* trie, char* destination){
    double time_spent = 0.0;
    clock_t begin = clock();

    FILE* result;
    FILE* ready;
    int count = 0;
    result = fopen("res_allFilms.txt", "w");

    preorderNmbFilms(trie, &count);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(result, "%s\n", destination);
    fprintf(result, "%f", time_spent); //j'insère le temps de la fonction
    fprintf(result, "\n%d", count);

    preorderFilms(trie, result);


    fclose(result);
    ready = fopen("ready3.txt", "w"); //Création du fichier prêt pour lecture du côté front end;
    fclose(ready);
}

void printTopDirector(struct NodeTrie* trie, char* destination){
    double time_spent = 0.0;
    clock_t begin = clock();

    FILE* result;
    FILE* ready;

    result = fopen("res_director.txt", "w");
    struct Director* topD = trie->topDirector;

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