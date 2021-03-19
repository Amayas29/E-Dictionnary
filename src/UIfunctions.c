#include "UIfunctions.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonctions locale dans le fichier
// Change str en majuscule et retourne le pointeur vers str
static char *maj(char *str);

int start(dictionary dict, char *filename) {
    initDict(dict);
    return fillDictionary(dict, filename);
}

int addWord(dictionary dict) {
    printf("Please enter the word to add : ");
    char *word = scanWord();
    word = maj(word);

    if (getWordFromDict(dict, word) != NULL) {
        free(word);
        return 1;
    }

    printf("Please enter the definition on the word : ");
    char *definition = scanWord();

    int res = addWordIntoDictionary(dict, word, definition);

    if (res != 0) {
        free(word);
        free(definition);
    }

    return res;
}

wordStruct *searchWord(dictionary dict) {
    printf("Please enter the word to search for : ");
    char *word = scanWord();
    word = maj(word);

    wordStruct *res = getWordFromDict(dict, word);

    free(word);

    return res;
}

int removeWord(dictionary dict) {
    printf("Please enter the word to delete : ");
    char *word = scanWord();
    word = maj(word);

    int res = removeWordFromDictionary(dict, word);

    free(word);

    return res;
}

void quit(dictionary dict) {
    freeDictionary(dict);
    printf("Goodbye");
}

char *scanWord() {
    char buff[MAX_LENGTH];
    char c;
    int i = 0;

    while (isspace((c = fgetc(stdin))))
        ;

    while (c != '\n' && i < MAX_LENGTH) {
        buff[i++] = c;
        c = fgetc(stdin);
    }

    char *word = malloc(sizeof(char) * i + 1);

    if (word == NULL) {
        fprintf(stderr, "Pointer allocation error\n");
        return NULL;
    }

    word = strncpy(word, buff, i);
    word[i] = '\0';
    return trim(word);
}

void displayMenuChoices() {
    printf("\n \n");
    printf("                 //::::::::::::::::::::::::::::::::::::::::::::::::::// \n");
    printf("                //                                                  //  \n");
    printf("               //            ENGLISH   DICTIONNARY                 //    \n");
    printf("              //                                                  //     \n");
    printf("             //:::::::::::::::::::::::::::::::::::::::::::::::::://       \n");
    printf("\n\n\n\n");
    printf("\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\t::                                                         ::\n");
    printf("\t::    1 ) -  SEARCH A DEFINITION FOR A WORD                ::\n");
    printf("\t::    2 ) -  ADD WORD                                      ::\n");
    printf("\t::    3 ) -  DELETE A WORD                                 ::\n");
    printf("\t::    4 ) -  EXIT                                          ::\n");
    printf("\t::                                                         ::\n");
    printf("\t:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n                                                YOUR CHOICE  :  ");
}

char *trim(char *str) {
    char *ibuf, *obuf;

    if (str) {
        for (ibuf = obuf = str; *ibuf;) {
            while (*ibuf && (isspace(*ibuf)))
                ibuf++;

            if (*ibuf && (obuf != str))
                *(obuf++) = ' ';

            while (*ibuf && (!isspace(*ibuf)))
                *(obuf++) = *(ibuf++);
        }
        *obuf = '\0';
    }
    return (str);
}

static char *maj(char *str) {
    int length = strlen(str);

    for (int i = 0; i < length; i++)
        str[i] = toupper(str[i]);

    return str;
}