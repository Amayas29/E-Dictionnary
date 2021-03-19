#include "word.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

wordStruct *createWord(char *word, char *definition) {
    if (word == NULL || definition == NULL)
        return NULL;

    wordStruct *sWord = malloc(sizeof(wordStruct));

    if (sWord == NULL) {
        fprintf(stderr, "Pointer allocation error\n");
        return NULL;
    }

    sWord->word = word;
    sWord->definition = definition;
    sWord->next = NULL;

    return sWord;
}

int addWordToList(wordStruct **listWords, wordStruct *sWord) {
    if (listWords == NULL) {
        fprintf(stderr, "Empty list pointer\n");
        return -1;
    }

    if (sWord == NULL) {
        fprintf(stderr, "Empty pointer\n");
        return -1;
    }

    sWord->next = *listWords;
    *listWords = sWord;

    return 0;
}

void removeWordFromList(wordStruct **listWords, wordStruct *sWord) {
    if (*listWords == sWord) {
        *listWords = (*listWords)->next;
        free(sWord->word);
        free(sWord->definition);
        free(sWord);
        return;
    }

    wordStruct *sw = *listWords;

    for (; sw; sw = sw->next) {
        if (sw->next == sWord) {
            sw->next = (sw->next)->next;
            free(sWord->word);
            free(sWord->definition);
            free(sWord);
            return;
        }
    }
}

wordStruct *getWordFromList(wordStruct *listWords, char *word) {
    if (word == NULL)
        return NULL;

    for (; listWords; listWords = listWords->next)
        if (strcmp(listWords->word, word) == 0)
            return listWords;

    return NULL;
}

void printWord(wordStruct *sWord) {
    if (sWord)
        printf("\t %s : %s", sWord->word, sWord->definition);
}

void freeListWords(wordStruct *listWords) {
    while (listWords) {
        wordStruct *tmp = listWords->next;

        free(listWords->word);
        free(listWords->definition);
        free(listWords);

        listWords = tmp;
    }
}