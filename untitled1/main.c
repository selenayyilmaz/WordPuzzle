#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <strings.h>


#define SIZE 10
#define MAX_WORDS 20


int score = 0;
int word_count = 3;


void createTable(char table[SIZE][SIZE]) {

    srand(time(NULL));

    // Fill the table with random letters
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Generate a random uppercase letter (A-Z)
            table[i][j] = '.';
        }
    }
}

void addWords(char tableSize[SIZE][SIZE], int row, int col, char direction,const char *word) {
    int len = strlen(word);

    // FOR DIRECTIONS WE NEED TO FORMALIZE THE WAYS = 'H' for "Horizontal", 'V' for "Vertical", 'D' for "Dioganal"
    for (int i = 0; i < len; i++) {
        if (direction == 'H') {
            tableSize[row][col+i] = toupper(word[i]);
        } else if (direction == 'V') {
            tableSize[row+i][col] = toupper(word[i]);
        } else if (direction == 'D') {
            tableSize[row+i][col+i] = toupper(word[i]);
        }
    }
}

void fillRemainingSpacesWithWords(char tableSize[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (tableSize[i][j] == '.') {
                tableSize[i][j] = 'A' + (rand() % 26);
            }

        }
    }
}

void printTable(char table[SIZE][SIZE]) {
    // Print the table
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", table[i][j]);
        }
        printf("\n");
    }
}

void markWord(char table[SIZE][SIZE], int row, int col, char direction,const char *word) {
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        if (direction == 'H') {
            table[row][col+i] = '-';
        } else if (direction == 'V') {
            table[row+i][col] = '-';
        } else if (direction == 'D') {
            table[row+i][col+i] = '-';
        }
    }

}

int findWords(char table[SIZE][SIZE],const char *word, int *score) {
    int len = strlen(word);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (j + len <= SIZE) {
                int k;
                for (k = 0; k < len; k++) {
                    if (toupper(table[i][j + k]) != toupper(word[k])) break;
                }
                if (k == len) {
                    markWord(table, i, j, 'H', word);
                    (*score)++;
                    return 1;
                }
            }

            // Check vertically
            if (i + len <= SIZE) {
                int k;
                for (k = 0; k < len; k++) {
                    if (toupper(table[i + k][j]) != toupper(word[k])) break;
                }
                if (k == len) {
                    markWord(table, i, j, 'V', word);
                    (*score)++;
                    return 1;
                }
            }

            // Check diagonally
            if (i + len <= SIZE && j + len <= SIZE) {
                int k;
                for (k = 0; k < len; k++) {
                    if (toupper(table[i + k][j + k]) != toupper(word[k])) break;
                }
                if (k == len) {
                    markWord(table, i, j, 'D', word);
                    (*score)++;
                    return 1;
                }
            }
        }
    }

    // Word not found
    (*score)--;
    return 0;
}

int main() {
    char guess[20];
    int remain_words = MAX_WORDS;
    char wordPuzzle[SIZE][SIZE];
    int foundSelam = 0, foundHello = 0, foundMerhaba = 0;

    printf("KELIME BULMACA OYUNUNA HOS GELDINIZ !\n");
    printf("Oyunu oynamaniz icin hazirlanan tablo:\n ");

    printf("\n");

    createTable(wordPuzzle);
    addWords(wordPuzzle, 2, 3,'H',"HELLO");
    addWords(wordPuzzle,5,5,'D',"SELAM");
    addWords(wordPuzzle,1,0,'V',"MERHABA");

    fillRemainingSpacesWithWords(wordPuzzle);

    printTable(wordPuzzle);

    printf("\n");

    printf("Tabloda belirlenmis 3 kelimeyi bulmaniz gerekmektedir. "
           "Tum kelimeleri bulunca oyun bitmektedir. \nKelimeyi her buldugunuzda +1 puan, bulamadiginizda ise -1 puan hanenize islenir."
           "\n\nOYUN BASLASIN !\n");

    while (1) {
        printf("Skorun %d\n",score);
        printf("Buldugunuz kelimeyi yazin:\n");
        scanf("%s",guess);


        if (strcasecmp(guess, "QUIT") == 0) {
            break;
        }

        if (strcasecmp(guess, "HELLO") == 0) {
            if (findWords(wordPuzzle, "HELLO",&score)) {
                foundHello = 1;
                printf("Tebrikler !");
            }
        } else if (strcasecmp(guess, "MERHABA") == 0) {
            if (findWords(wordPuzzle, "MERHABA",&score)) {
                foundMerhaba = 1;
                printf("Tebrikler !");
            }
        } else if (strcasecmp(guess, "SELAM") == 0) {
            if (findWords(wordPuzzle, "SELAM",&score)) {
                foundSelam = 1;
                printf("Tebrikler !");
            }
        } else {
            score --;
            printf("Yanlış cevap");
        }

        printTable(wordPuzzle);

        if (foundSelam && foundHello && foundMerhaba) {
            printf("Oyununuz bitti. Skorunuz %d",score);
            break;
        }
    }
}












