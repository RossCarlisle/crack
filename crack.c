/* Ross Carlisle
 * Cracks a alphabetic password, upper and lower case, 
 * from a C's crypt() DES 13 character hash using a simple brute force solution
 * https://docs.cs50.net/2017/fall/psets/2/crack/crack.html 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _XOPEN_SOURCE
#include <crypt.h>

void crackMatch(char* guess, char* salt, char* hash);

time_t start;

int main(int argc, char* argv[]) {

    start = time(NULL);

    if(argc != 2 || argv[1] == NULL || strlen(argv[1]) != 13) {
        printf("Usage: ./crack hash\n");
        printf("Requires a 13 character DES hash\n");
        return 1;
    }

    char* hash = argv[1];
    char salt[3] = {hash[0], hash[1], '\0'};

    // Guess(length of guess)[length + 1 for NUL character]
    char guess1[2], guess2[3], guess3[4], guess4[5], guess5[6];
    guess1[1] = '\0';
    guess2[2] = '\0';
    guess3[3] = '\0';
    guess4[4] = '\0';
    guess5[5] = '\0';

    char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alphabetLength = strlen(alphabet);

    printf("Searching...\n");

    // Simple brute force for all combinations of a password increasing in length
    for(int letter0 = 0; letter0 < alphabetLength; letter0++) {

        guess1[0] = alphabet[letter0];
        crackMatch(guess1, salt, hash);

        for(int letter1 = 0; letter1 < alphabetLength; letter1++) {

            guess2[0] = alphabet[letter0];
            guess2[1] = alphabet[letter1];
            crackMatch(guess2, salt, hash);

            for(int letter2 = 0; letter2 < alphabetLength; letter2++) {

                guess3[0] = alphabet[letter0];
                guess3[1] = alphabet[letter1];
                guess3[2] = alphabet[letter2];
                crackMatch(guess3, salt, hash);

                for(int letter3 = 0; letter3 < alphabetLength; letter3++) {

                    guess4[0] = alphabet[letter0];
                    guess4[1] = alphabet[letter1];
                    guess4[2] = alphabet[letter2];
                    guess4[3] = alphabet[letter3];
                    crackMatch(guess4, salt, hash);

                    for(int letter4 = 0; letter4 < alphabetLength; letter4++) {

                        guess5[0] = alphabet[letter0];
                        guess5[1] = alphabet[letter1];
                        guess5[2] = alphabet[letter2];
                        guess5[3] = alphabet[letter3];
                        guess5[4] = alphabet[letter4];
                        crackMatch(guess5, salt, hash);

                    }
                }
            }
        }
    }

    return 0;
}

void crackMatch(char* guess, char* salt, char* hash) {

    if(strcmp(crypt(guess, salt), hash) == 0) {
        double timeSpent = (double) (time(NULL) - start);
        timeSpent = timeSpent / 60;
        int minutes = timeSpent;
        int seconds = ((timeSpent - minutes) * 60);
        printf("%s\n", guess);
        if(minutes > 0) {
            printf("Found in %i minutes %i seconds\n", minutes, seconds);
        } else {
            printf("Found in %i seconds\n", seconds);
        }
        exit(0);
    }

}
