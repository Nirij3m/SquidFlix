
#ifndef C_FILM_H
#define C_FILM_H
#include "listDirector.h"
#include "listFilm.h"
#include "hashTableDirectorList.h"
#include "hashTableFilmList.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>




struct HashTable* readDirectors(char* fileName, struct ListFilm** timeArray, struct HashTableFilm* genreTable, struct HashTableFilm* filmTable);
struct CellFilm** timeArray(char* fileName);
void findByDirector(char* director, struct HashTable* ht, char* destination);
void findByGenre(char* genre, struct HashTableFilm* genres, char* destination);
void findByDuration(int duration, struct ListFilm** timeArray, char* destination);
void randomFilm(struct HashTableFilm* films, char* destination);
void allDirectors(struct HashTable* dir, char* destination);
void printTopDirector(struct HashTable* dir, char* destination);
void clearInput();
void addFilm(struct HashTableFilm* films, struct HashTable* directors, char* director, char* genre, char* title, int duration);
void createAccount(char* hashUser, char* hashPass);

#endif //C_FILM_H
