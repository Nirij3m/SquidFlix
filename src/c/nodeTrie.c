#include "nodeTrie.h"
#include "listDirector.h"
#include "listFilm.h"

struct NodeTrie* createEmptyNodeTrie(){
    struct NodeTrie* trie = malloc(sizeof(struct NodeTrie));
    if(trie != NULL){
        for (int i = 0; i < MAX_SIZE; i++){
            trie->alphabets[i] = NULL;
        }
        trie->isWord = false;
        trie->films = createEmptyListFilm();
        trie->topDirector = malloc(sizeof(struct Director));
        trie->topDirector = NULL;
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

void insertWord(struct NodeTrie* trie, char* word, struct CellFilm* film, struct Director* topDirector, int* maxSize){
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
    //Check the best director
    int listSize = listSizeFilm(currentNode->films);
    if(maxSize != NULL && listSize > *maxSize){
       *maxSize = listSize; //Nouvelle taille à comparer
       topDirector->nmbFilm = listSize; //Change la taille du directeur
       free(topDirector->name);
       topDirector->name = malloc((strlen(word)+1)*sizeof(char));
       strcpy(topDirector->name, word);
       topDirector->films = currentNode->films; //Je fais pointer la listFilm du directeur actuel vers la nouvelle
    }
    if(topDirector != NULL) {
        currentNode->films->director = malloc((strlen(word) + 1) * sizeof(char)); //Je copie le nom du directeur en rappel
        strcpy(currentNode->films->director, word);
    }
    addFirstFilm(currentNode->films, film->nomFilm, film->duration, film->genre);
}

void deleteWord(struct NodeTrie* trie, char* word){
    unsigned int n = strlen(word);
    for (int i = 0; i < n; i++){
        int index = word[i] - 'a';
        if (trie->alphabets[index] == NULL){
            return;
        }
        trie = trie->alphabets[index];
    }
    trie->isWord = false;
}

void deleteNodeTrie(struct NodeTrie** trie){
    if ((*trie) != NULL){
        for (int i = 0; i < MAX_SIZE; i++){
            if ((*trie)->alphabets[i] != NULL){

                struct ListFilm* l = (*trie)->films;
                if(!(*trie)->isWord){
                    free((*trie)->films);
                }
                else{
                    if(l->director != NULL) { // Je regarde si'ol y a un nom dirctor à free
                        free(l->director);
                    }
                    unsigned int size = listSizeFilm(l);
                    for(int i = 0; i < size; i++){
                        deleteFirstFilm(l);
                    }
                    free((*trie)->films);
                }

                if((*trie)->topDirector != NULL){ //Il y a un topDirector à free
                    free((*trie)->topDirector->name);
                    //Delete la liste de film
                    unsigned int otherSize = listSizeFilm((*trie)->topDirector->films);
                    for(int i = 0; i < otherSize; i++){
                        deleteFirstFilm((*trie)->topDirector->films);
                    }
                }
                deleteNodeTrie(&((*trie)->alphabets[i]));
            }
        }
        *trie = NULL;
    }
    else{
        printf("error free");
    }
}

bool findWord(struct NodeTrie* trie, char* word){
    unsigned int n = strlen(word);
    for (int i = 0; i < n; i++){
        int index = word[i] - 'a';
        if (trie->alphabets[index] == NULL){
            return false;
        }
        trie = trie->alphabets[index];
    }
    return trie->isWord;
}

unsigned int numberOfWords(struct NodeTrie* trie){
    unsigned int count = 0;
    if (trie->isWord){
        count++;
    }
    for (int i = 0; i < MAX_SIZE; i++){
        if (trie->alphabets[i] != NULL){
            count += numberOfWords(trie->alphabets[i]);
        }
    }
    return count;
}

struct NodeTrie* readDict(char *filename, struct ListFilm** timeArray, struct NodeTrie* genres){
    struct NodeTrie* trie = createEmptyNodeTrie();
    struct Director* topD = createCellDirector("init");
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
        struct CellFilm *film = createCellFilm(title, duration, genre);
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
        insertWord(trie, director, film, topD, &bestSize);
        insertWord(genres, genre, film, NULL, NULL);
        insertFilm(timeArray, title, duration, genre);

    }
    trie->topDirector = topD; //Je fais poiter le topDirector of topD trouvé

    fclose(request);
    return trie;
}

void displayDict( struct NodeTrie* trie, char* preword, char* word, int index){
    if (trie->isWord){
        word[index] = '\0';
        printf(" - %s%s", preword, word);
    }
    for (int i = 0; i < MAX_SIZE; i++){
        if (trie->alphabets[i] != NULL){
            word[index] = i + 'a';
            displayDict(trie->alphabets[i], preword, word, index + 1);
        }
    }
}

void findWords(struct NodeTrie* dict, char* preword, char* letters, int index){
    bool valid = true;
    char prefix[32];
    struct NodeTrie* currentNode = dict;
    for (int i = 0; i < strlen(letters); i++) {
        int ind = letters[i] - 'a';
        if (currentNode->alphabets[ind] == NULL) { //Pas trouver, je renvoie le plus proche
            valid = false;
            printf("\nNo word %s in dictionary", letters);
            break;
        }
        currentNode = currentNode->alphabets[ind];
    }
    if (valid == true) { //J'ai trouvé je renvoie la liste
    printf("\nWords starting with %s : \n", letters);
    displayDict(currentNode, preword, prefix, 0);
    }
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











