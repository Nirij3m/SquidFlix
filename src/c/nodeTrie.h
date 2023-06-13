#ifndef nodeTrie
#define nodeTrie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "listFilm.h"



#define MAX_SIZE 26 // 26 alphabets


struct NodeTrie {
    bool isWord;
    struct NodeTrie* alphabets [MAX_SIZE];
    struct ListFilm* films;
    struct Director* topDirector;
};

struct NodeTrie* readDict(char *filename, struct ListFilm** timeArray, struct NodeTrie* genres);

struct NodeTrie* createEmptyNodeTrie();
bool isNodeTrieEmpty(struct NodeTrie* trie);
void insertWord(struct NodeTrie* trie, char* word, struct CellFilm* film, struct Director* d);
void insertWordGenre(struct NodeTrie* trie, char* word, struct CellFilm* film); //same as insertWord but do not copy the director
void deleteWord(struct NodeTrie* trie, char* word);
bool findWord(struct NodeTrie* trie, char* word);
void deleteNodeTrie(struct NodeTrie** trie);
unsigned int numberOfWords( struct NodeTrie* trie );

void displayDict( struct NodeTrie* trie, char* preword, char* word, int index);
void findWords(struct NodeTrie* dict, char* preword, char* letters, int index);
struct ListFilm* findDirector(struct NodeTrie* dict, char* preword, char* letters, int index);
void remove_spaces(char *str);
void remove_schar(char* str);
void preorderFilms(struct NodeTrie* node, FILE* result);
void preorderDirector(struct NodeTrie* node, FILE* result);
void preorderNmbFilms(struct NodeTrie* node, int* count);
void preorderTopDirector(struct NodeTrie* node, int* count, char* director);
void separateString(char* input, char** output);
#endif
