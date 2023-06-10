
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
void findByDirector(char* director);
void findByGenre(char* genre);
void findByDuration(int duration);
void randomFilm();


#endif //C_FILM_H
