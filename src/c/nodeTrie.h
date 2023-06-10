#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 26 // 26 alphabets


struct NodeTrie {
    bool isWord;
    struct NodeTrie* alphabets [MAX_SIZE];
};


struct NodeTrie* createEmptyNodeTrie();
bool isNodeTrieEmpty(struct NodeTrie* trie);
void insertWord(struct NodeTrie* trie, char* word);
void deleteWord(struct NodeTrie* trie, char* word);
bool findWord(struct NodeTrie* trie, char* word);
void deleteNodeTrie(struct NodeTrie** trie);
unsigned int numberOfWords( struct NodeTrie* trie );
struct NodeTrie* readDict(char *filename);
void displayDict( struct NodeTrie* trie, char* preword, char* word, int index);
void findWords(struct NodeTrie* dict, char* preword, char* letters, int index);
