
#ifndef C_FILM_H
#define C_FILM_H
#include "listDirector.h"
#include "listFilm.h"
#include "nodeTrie.h"
#include <string.h>



void findByDirector(char* name);
void findByGenre(char* genre);
void findByDuration(int duration);
void randomFilm();


#endif //C_FILM_H
