#include "hashfunctions.h"

#include <string.h>

#define NUMBER_HASH 171482;

int firstHashage(char *word) {
    int hash = 0;
    int length = strlen(word);

    for (int i = 0; i < length; i++) {
        if (word[i] != ' ' && word[i] != '-')
            hash = (hash * 100 + word[i] - 65) % NUMBER_HASH;

        // Si la lettre est un tiret on rajoute que 27
        if (word[i] == '-')
            hash += 27;
    }

    return hash;
}

int secondHashage(char *word) {
    int hash = 0;
    int length = strlen(word);

    for (int i = 1; i < length; i++) {
        hash += word[i] * i;
    }

    return hash;
}
