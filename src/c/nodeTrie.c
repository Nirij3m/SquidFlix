#include "nodeTrie.h"

#include "listFilm.h"

struct NodeTrie* createEmptyNodeTrie(){
    struct NodeTrie* trie = malloc(sizeof(struct NodeTrie));
    if(trie != NULL){
        for (int i = 0; i < MAX_SIZE; i++){
            trie->alphabets[i] = NULL;
        }
        trie->isWord = false;
        trie->films = createEmptyListFilm();
        return trie;
    }
    else{
        printf("error malloc");
        return NULL;
    }
}

bool isNodeTrieEmpty(struct NodeTrie* trie) {
    if (trie == NULL) {
        return true;
    }
    return false;
}

void insertWord(struct NodeTrie* trie, char* word, struct CellFilm* film, struct Director* d){
    unsigned int len = strlen(word);
    struct NodeTrie *currentNode = trie;
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (currentNode->alphabets[index] == NULL) {
            currentNode->alphabets[index] = createEmptyNodeTrie();
        }
        currentNode = currentNode->alphabets[index];
    }
    currentNode->isWord = true;
    //je copie le directeur dans la liste de film
    if(currentNode->films->director == NULL){ //Créer et copie le directeur ssi il n'existe pas
        currentNode->films->director = malloc((strlen(word)+1)*sizeof(char));
        strcpy(currentNode->films->director, word);
    }
    //Comparaison pour le topDirector
    if(currentNode->films->size > d->nmbFilm){
        d->nmbFilm = currentNode->films->size;
        if(d->name != NULL){ // le nom existe déjà je le libère
            free(d->name);
            d->name = NULL;
            d->name = malloc((strlen(word)+1)*sizeof(char));
            strcpy(d->name, word);
        }
        else{ //le nom n'existe pas
            d->name = malloc((strlen(word)+1)*sizeof(char));
            strcpy(d->name, word);
        }

    }
    addFirstFilm(currentNode->films, film);

}

void insertWordGenre(struct NodeTrie* trie, char* word, struct CellFilm* film){
    unsigned int len = strlen(word);
    struct NodeTrie *currentNode = trie;
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (currentNode->alphabets[index] == NULL) {
            currentNode->alphabets[index] = createEmptyNodeTrie();

            if(currentNode->alphabets[index] == NULL){
                while(true){
                    printf("NODE TRIE ERROR MALLOC");
                }
            }
        }
        currentNode = currentNode->alphabets[index];
    }
    currentNode->isWord = true;
    //je copie le directeur dans la liste de film
    addFirstFilm(currentNode->films, film);

}


void deleteNodeTrie(struct NodeTrie** trie){
    if ((*trie) != NULL){
        for (int j = 0; j < MAX_SIZE; j++){
            if ((*trie)->alphabets[j] != NULL){
                    if((*trie)->alphabets[j]->topDirector != NULL){
                        deleteDirector((*trie)->alphabets[j]->topDirector);
                    }
                    if((*trie)->alphabets[j]->films != NULL){
                        deleteListFilm(&((*trie)->alphabets[j]->films ));
                    }
                    if( (*trie)->films != NULL && (*trie)->films->director != NULL){
                        free((*trie)->films->director);
                        (*trie)->films->director = NULL;
                    }
                deleteNodeTrie(&((*trie)->alphabets[j])); //appel récursif
            }
        }

        //Je supprime le pointeur à film
        if((*trie)->films != NULL && listSizeFilm((*trie)->films) != 0 ){
            free((*trie)->films);
            (*trie)->films = NULL;
        }

        //Je supprime le char director
        if( (*trie)->films != NULL && (*trie)->films->director != NULL){
            free((*trie)->films->director);
            (*trie)->films->director = NULL;
        }
        //Je supprime le topDirector
        if((*trie)->topDirector != NULL){
            deleteDirector((*trie)->topDirector);
        }
        free(*trie);
        *trie = NULL;
    }
    else{
        printf("error free");
    }
}


struct NodeTrie* readDict(char *filename, struct ListFilm** timeArray, struct NodeTrie* genres){
    struct NodeTrie* trie = createEmptyNodeTrie();
    struct Director* d = malloc(sizeof(struct Director));
    d->name = NULL;


    int bestSize = 0;
    FILE *request = fopen(filename, "r");
    if (request == NULL){
        printf("error opening file");
        deleteNodeTrie(&trie);
        return NULL;
    }

    char director[320];
    char title[320];
    int duration;
    char genre[320];

    while (!feof(request)) { //Requête arrivée
        memset(director, '\0', 320);
        memset(title, '\0', 320);
        memset(genre, '\0', 320);

        fscanf(request, "%[^;];%[^;];%d;%[^\n]\n", director, title, &duration, genre);
        genre[strcspn(genre, "\r")] = '\0'; //retire l'éventuel "\n"
        //création du film
        struct CellFilm* film1 = createCellFilm(title, duration, genre);
        struct CellFilm* film2 = createCellFilm(title, duration, genre);
        struct CellFilm* film3 = createCellFilm(title, duration, genre);
        //Lower case
        for(int i = 0; director[i]; i++){
            director[i] = tolower(director[i]);
        }
        for(int i = 0; genre[i]; i++){
            genre[i] = tolower(genre[i]);
        }
        //Remove spaces
        remove_spaces(director);
        remove_schar(director);
        remove_spaces(genre);
        remove_schar(genre);
        insertWord(trie, director, film1, d);
        insertWordGenre(genres, genre, film2);
        insertFilm(timeArray, film3);
    }
    trie->topDirector = d;
    fclose(request);
    return trie;
}


struct ListFilm* findDirector(struct NodeTrie* dict, char* preword, char* letters, int index){
    bool valid = true;
    struct NodeTrie* currentNode = dict;
    for (int i = 0; i < strlen(letters)+1; i++) {
        int ind = letters[i] - 'a';
        if (currentNode->alphabets[ind] == NULL || i == strlen(letters)) { //Pas trouver, je renvoie le plus proche
            valid = false;
            while(!currentNode->isWord){ //Tant que pas de director

                for(int i = 0; i < 26; i++){
                    if(currentNode->alphabets[i] != NULL){ //Parcours alphabet tant que noeud vide
                        currentNode = currentNode->alphabets[i];
                    }
                }
            }
            //j'ai trouvé le noeud le plus proche
            return currentNode->films;
        }
        currentNode = currentNode->alphabets[ind];
    }
    if (valid == true) { //J'ai trouvé je renvoie la liste
        printf("\nDid you search for %s ? \n", letters);
        return currentNode->films;
    }
}

void remove_spaces(char *str)
{
    int count = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i];
    str[count] = '\0';
}

void remove_schar(char* str){
    int i, j;
    for(i = 0; str[i] != '\0'; ++i)
    {
        while (!( (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '\0') )
        {
            for(j = i; str[j] != '\0'; ++j)
            {
                str[j] = str[j+1];
            }
            str[j] = '\0';
        }
    }
}

void preorderFilms(struct NodeTrie* node, FILE* result) {
    if (node == NULL) {
        return;
    }

    if(node->isWord){
        int size = listSizeFilm(node->films);
        struct CellFilm* iter = node->films->head;
        for(int j = 0; j < size; j++){
            fprintf(result, "\n%s;%d;%s", iter->nomFilm, iter->duration, iter->genre);
            iter = iter->next;
        }
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        preorderFilms(node->alphabets[i], result);
    }
}

void preorderDirector(struct NodeTrie* node, FILE* result) {
    if (node == NULL) {
        return;
    }

    if(node->isWord){
        fprintf(result, "\n%s", node->films->director);
    }

    for (int i = 0; i < MAX_SIZE; i++) {
        preorderDirector(node->alphabets[i], result);
    }
}

void preorderNmbFilms(struct NodeTrie* node, int* count) {
    if (node == NULL)
        return;

    if(node->isWord){
        *count += node->films->size;
    }
    for (int i = 0; i < MAX_SIZE; i++) {
        preorderNmbFilms(node->alphabets[i], count);
    }
}












