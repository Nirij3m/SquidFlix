
#ifndef C_FILM_H
#define C_FILM_H
#include "listDirector.h"
#include "listFilm.h"
#include "hashTableDirectorList.h"


bool addFilm(struct CellFilm* film, struct Director* d);
struct ListDirector* readDatabase(char* nameFile);
void findByDirector(char* name);
void findByGenre(char* genre);
void findByDuration(int duration);
void randomFilm();


#endif //C_FILM_H
