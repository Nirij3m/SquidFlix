#include "hashTableDirectorList.h"
#include "hashTableFilmList.h"
#include "databaseInit.h"


int main() {

    //INITI DATABASE
    double time_spent = 0.0;
    clock_t begin = clock();
    struct ListFilm** timeArray = createTimeArray();
    struct HashTableFilm* films = createEmptyHashTableFilm(1000);
    struct HashTableFilm* genres = createEmptyHashTableFilm(130);
    struct HashTable* lib = readDirectors("BD_medium.txt", timeArray, genres, films);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Database initialized in: %fs\n", time_spent);
    //END

    //printHashTableFilm(genres);

    //findByDuration(499, timeArray);
    //findByDirector("Haam", lib);
    //randomFilm(films);
    //allDirectors(lib);
    //findByGenre("Western", genres);

    //LISTNER INCOMMING REQUESTS
    bool stopInit = false;
    remove("request.txt");
    remove("results.txt");
    remove("ready.txt");

    while(!stopInit) {
        printf("Listenning for incomming request...\n");
        FILE *request;
        request = fopen("request.txt", "r");
        char functionCalled[32];
        char parameter[32];
        char* destination;

        while (request == NULL) { //Tant qu'un fichier request.txt n'est pas arrivée, je continue de le chercher
            request = fopen("request.txt", "r");
        }
        while (!feof(request)) { //Requête arrivée
            printf("Request found!\n");
            fscanf(request, "%[^;];%[^;];%[^\n]\n", destination, functionCalled, parameter);
            parameter[strcspn(parameter, "\r")] = '\0'; //retire l'éventuel "\n"

            //Je teste toutes les fonctions possibles à appeler
            if (strcmp(functionCalled, "findByDirector") == 0) {
                findByDirector(parameter, lib, destination);
                clearInput(); //removes the ready.txt and the results.txt
            }
            if (strcmp(functionCalled, "findByGenre") == 0) {
                findByGenre(parameter, genres, destination);
                clearInput();
            }
            if (strcmp(functionCalled, "findByDuration") == 0) {
                findByDuration(atoi(parameter), timeArray, destination);
                clearInput();
            }
            if (strcmp(functionCalled, "randomFilm") == 0) {
                randomFilm(films, destination);
                clearInput();
            }
            if (strcmp(functionCalled, "allDirectors") == 0) {
                allDirectors(lib, destination);
                clearInput();
            }
            if (strcmp(functionCalled, "printTopDirector") == 0) {
                printTopDirector(lib, destination);
                clearInput();
            }
            if (strcmp(functionCalled, "deleteDatabase") == 0){
                printf("Databsase clear procedure intialized");
                stopInit = true; //will stop the infinite loop after the database have been cleared
                freeTimeArray(timeArray);
                deleteHashTableFilm(&films);
                deleteHashTableFilm(&genres);
                deleteHashTable(&lib);
            }
            //Clear the input to avoid artefacts
            memset(functionCalled, '\0', sizeof(char) * 32);
            memset(parameter, '\0', sizeof(char) * 32);
        }
        //J'ai lu toute la requête, je peux la supprimer
        remove("request.txt");
        fclose(request);
    }
    //END

return 0;
}

