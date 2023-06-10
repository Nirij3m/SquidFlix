#include "hashTableDirectorList.h"
#include "hashTableFilmList.h"
#include "databaseInit.h"
#define BUCKET_SIZE 5
void testHashTableIDirector();

int main() {

    //printHashTable(directors);
    //printf("\n");
    //printTimeArray(timeArray);
    //printf("\n");
    //printHashTableFilm(genreTable);
    //printf("\n");
    //printHashTableFilm(filmTable);

    //findByDirector("Yeung");
    //randomFilm();
    findByDuration(132);

return 0;
}

void testHashTableIDirector(){

    struct HashTable* h1 = createEmptyHashTable(BUCKET_SIZE);
    insert(h1, "Bob", "Vroum", 150, "Comedy");
    insert(h1, "Bob", "Papacito", 11, "Drouate");
    insert(h1, "Alex", "Malo", 2, "Drama");
    insert(h1, "Roger", "camp", 2, "Drama");
    insert(h1, "Mina", "rat", 2, "Drama");
    insert(h1, "Jeanne", "papr", 2, "Drama");

    printHashTable(h1);
    printListFilm(h1->table[4]->head->films);

    deleteHashTable(&h1);

}
