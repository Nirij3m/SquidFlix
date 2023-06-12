
#ifndef C_FILM_H
#define C_FILM_H
#include "listDirector.h"
#include "listFilm.h"
#include "nodeTrie.h"
#include "hashTableFilmList.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>




struct HashTable* readDirectors(char* fileName, struct ListFilm** timeArray, struct HashTableFilm* genreTable, struct HashTableFilm* filmTable);
struct CellFilm** timeArray(char* fileName);

void findByDirector(char* director, struct NodeTrie* trie, char* destination);
void findByGenre(char* genre, struct NodeTrie* genres, char* destination);
void findByDuration(int duration, struct ListFilm** timeArray, char* destination);
void randomFilm(struct ListFilm** timeArray, char* destination);
void allDirectors(struct NodeTrie* trie, char* destination);
void allFilms(struct NodeTrie* trie, char* destination);
void printTopDirector(struct NodeTrie* trie, char* destination);
void clearInput();
void addFilm(struct HashTableFilm* films, struct NodeTrie* trieectors, char* director, char* genre, char* title, int duration);
void createAccount(char* hashUser, char* hashPass);

#endif //C_FILM_H
