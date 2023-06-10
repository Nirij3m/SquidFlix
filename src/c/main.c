#include "nodeTrie.h"

int main() {

    //creates an empty trie that will act as our dictionaries

    char filename[] = "BD_small.txt";
    struct NodeTrie *root = readDict(filename);
    char prefix[32];
    prefix[0] = '\0';
    char exit[1] = "#";
    char del[1] = "*";

    //displays the trie

    char letter;
    char wordLetters[32];
    bool isTrue = true;
    bool isDel = false;

    displayDict(root, wordLetters, prefix, 0);

    while (isTrue == true) {
        isDel = false;
        printf("\n\nYour word: %s\n", wordLetters);
        printf("\n* to delete or # to exit");
        printf("\nEnter a letter to add: ");
        scanf("\n%c", &letter);

        //if the latest letter is # then the program ends
        if (letter == exit[0]) {
            printf("\n\nThank you for using my program!\n");
            printf("\nI also want to give a special thanks to Achille, who helped me add the missing letters to the dictionary words!\n\n");
            isTrue = false;
            break;
        }
        //if the latest letter is * then the program deletes the last letter from wordLetters and displays the words that start with the new wordLetters
        if (letter == del[0]) {
            // will have to delete the last letter from wordLetters and the star included
            wordLetters[strlen(wordLetters) - 1] = '\0';
            prefix[strlen(prefix) - 1] = '\0';
            strcpy(prefix, wordLetters);
            isDel = true;
            findWords(root, wordLetters, prefix, 0);
            printf("\n\nA letter has been deleted from your word!");

        }
        //the isDel boolean is helpful to know if the person has deleted a letter start from the beginning of the loop
        if (isDel == false) {
            wordLetters[strlen(wordLetters)] = letter;
            wordLetters[strlen(wordLetters)] = '\0';
            strcpy(prefix, wordLetters);
            findWords(root, wordLetters, prefix, 0);
        }
    }

    //free the memory
    deleteNodeTrie(&root);
    return 0;
}
