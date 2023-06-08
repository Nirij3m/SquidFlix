
#ifndef C_FILM_H
#define C_FILM_H

#include "assets/listFilm.h"
#include "assets/hashTableDirectorList.h"



struct Director {
    char* name;
    int nmbFilm;
    struct ListFilm** films;
};

void findByDirector(char* name);
void findByGenre(char* genre);
void findByDuration(int duration);
void randomFilm();


#endif //C_FILM_H
