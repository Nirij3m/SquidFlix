#include "assets/listFilm.h"

int main() {

   struct ListFilm* l1 = createEmptyListFilm();
   addFirstFilm(l1, "Jeanne", 150, "Comedy");
    addFirstFilm(l1, "Robert", 20, "Drame");
    addFirstFilm(l1, "Pierre", 230, "Western");
    printListFilm(l1);

   struct CellFilm* c1 =  filmBelongs(l1,"Pierre", 230, "Western");

    deleteFirstFilm(l1);
    printListFilm(l1);
    deleteListFilm(&l1);

}
