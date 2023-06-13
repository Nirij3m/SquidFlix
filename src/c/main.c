#include "nodeTrie.h"

#include "databaseInit.h"
#include <ctype.h>


int main() {

    //INITI DATABASE
    double time_spent = 0.0;
    clock_t begin = clock();
    struct ListFilm **timeArray = createTimeArray();
    struct NodeTrie* genres = createEmptyNodeTrie();
    struct NodeTrie *root = readDict("BD_medium.txt", timeArray, genres);

    clock_t end = clock();
    time_spent += (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Database initialized in: %fs\n", time_spent);
    //END

    //RENVOIE TOP DIRECTOR, RANDOM FILMS, ALLFILMS
    //printTopDirector(lib,"T");
    randomFilm(timeArray, "A");
    printTopDirector(root, "T");
    allDirectors(root, "D");
    allFilms(root, "F");
    //END


    //LISTNER INCOMMING REQUESTS
    bool stopInit = false;
    remove("request.txt");
    remove("results.txt");
    remove("ready.txt");

    while(!stopInit) {
        printf("Listenning for incomming request...\n");
        FILE *request;
        request = fopen("request.txt", "r");
        char functionCalled[232];
        char parameter[232];
        char destination[2];
        char preword[232];

        while (request == NULL) { //Tant qu'un fichier request.txt n'est pas arrivée, je continue de le chercher
            request = fopen("request.txt", "r");
        }
        while (!feof(request)) { //Requête arrivée
            printf("Request found!\n");
            fscanf(request, "%[^;];%[^;];%[^\n]\n", destination, functionCalled, parameter);
            parameter[strcspn(parameter, "\r")] = '\0'; //retire l'éventuel "\n"
            memset(preword, '\0', 32);

            //Je teste toutes les fonctions possibles à appeler
            if (strcmp(functionCalled, "findByDirector") == 0) {
                for(int i = 0; parameter[i]; i++){
                    parameter[i] = tolower(parameter[i]);
                }
                remove_spaces(parameter);
                remove_schar(parameter);
                findByDirector(parameter, root, destination);
                clearInput(); //removes the ready.txt and the results.txt
            }
            if (strcmp(functionCalled, "findByGenre") == 0) {
                remove_spaces(parameter);
                remove_schar(parameter);
                for(int i = 0; parameter[i]; i++){
                    parameter[i] = tolower(parameter[i]);
                }
                findByGenre(parameter, genres, destination);
                clearInput();
            }
            int newDuration = atoi(parameter);

            if (strcmp(functionCalled, "findByDuration") == 0) {
                findByDuration(newDuration, timeArray, destination);
                clearInput();
            }
            if (strcmp(functionCalled, "randomFilm") == 0) {
                randomFilm(timeArray, destination);
                clearInput();
            }
            if (strcmp(functionCalled, "allDirectors") == 0) {
                allDirectors(root, destination);
                clearInput();
            }
            if (strcmp(functionCalled, "allFilms") == 0) {
                allFilms(root, destination);
                clearInput();
            }
            if (strcmp(functionCalled, "printTopDirector") == 0) {
                printTopDirector(root, destination);
                clearInput();
            }
            if (strcmp(functionCalled, "deleteDatabase") == 0){
                printf("Databsase clear procedure intialized");
                stopInit = true; //will stop the infinite loop after the database have been cleared
                freeTimeArray(timeArray);
                deleteNodeTrie(&genres);
                deleteNodeTrie(&root);
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
