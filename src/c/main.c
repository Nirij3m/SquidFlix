#include "hashTableDirectorList.h"
#include "databaseInit.h"
#define BUCKET_SIZE 5
void testHashTableIDirector();

int main() {
    struct HashTable* tableDirectors = readDirectors("BD_medium.txt");
    printHashTable(tableDirectors);
    printListFilm(tableDirectors->table[1198]->head->films);

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
