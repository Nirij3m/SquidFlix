#include "databaseInit.h"

bool addFilm(char* nomFilm, int duration, char* genre, struct Director* d){
    addFirstFilm(d->films, nomFilm, duration, genre);
}
