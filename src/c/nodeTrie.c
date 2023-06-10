#include "nodeTrie.h"

struct NodeTrie* createEmptyNodeTrie(){
    struct NodeTrie* trie = malloc(sizeof(struct NodeTrie));
    if(trie != NULL){
        for (int i = 0; i < MAX_SIZE; i++){
            trie->alphabets[i] = NULL;
        }
        trie->isWord = false;
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

void insertWord(struct NodeTrie* trie, char* word){
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
                deleteNodeTrie(&((*trie)->alphabets[i]));
            }
        }
        free(*trie);
        *trie = NULL;
    }
    else{
        printf("error free");
    }
}


struct NodeTrie * readDict(char *filename){
    struct NodeTrie* trie = createEmptyNodeTrie();
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        printf("error opening file");
        deleteNodeTrie(&trie);
        return NULL;
    }
    char word[256];
    char title[256];
    char director[256];
    int duration = 0;
    char genre[256];

    while (!feof(file)){
        fscanf(file, "%[^;];%[^;];%d;%[^\n]\n", director, title, &duration, genre),
        genre[strcspn(word, "\r")] = '\0'; //
        insertWord(trie, director);
    }
    fclose(file);
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
        if (currentNode->alphabets[ind] == NULL) {
            valid = false;
            printf("\nNo word %s in dictionary", letters);
            break;
        }
        currentNode = currentNode->alphabets[ind];
    }
    if (valid == true) {
    printf("\nWords starting with %s : \n", letters);
    displayDict(currentNode, preword, prefix, 0);
    }
}











