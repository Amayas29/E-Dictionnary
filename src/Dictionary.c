#include "Dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashfunctions.h"

void initDict(dictionary dict) {
    for (int i = 0; i < NUMBER_LETTERS; i++) {
        dict[i].lengthTabLetter = 0;
        dict[i].tabletter = NULL;
    }
}

wordStruct *getWordFromDict(dictionary dict, char *word) {
    if (word == NULL)
        return NULL;

    int hash1 = firstHashage(word);
    int hash2 = secondHashage(word);

    int i = 0;
    while (word[i] != '\0' && word[i] == '-')
        i++;

    if (word[i] == '\0')
        return NULL;

    int firstLetter = word[i] - 65;

    int length1 = dict[firstLetter].lengthTabLetter;

    if (length1 <= hash1 || !dict[firstLetter].tabletter)
        return NULL;

    int length2 = dict[firstLetter].tabletter[hash1].lengthtab2;

    if (length2 <= hash2 || !dict[firstLetter].tabletter[hash1].htab2 || !dict[firstLetter].tabletter[hash1].htab2[hash2])
        return NULL;

    return getWordFromList(dict[firstLetter].tabletter[hash1].htab2[hash2], word);
}

int rebuildStructure(dictionary dict, int firstLetter, int hash1, int hash2) {
    int length1 = dict[firstLetter].lengthTabLetter;

    if (length1 == 0) {
        dict[firstLetter].tabletter = malloc(sizeof(phash));

        if (dict[firstLetter].tabletter == NULL) {
            fprintf(stderr, "Pointer allocation error\n");
            return -1;
        }
    }

    if (length1 <= hash1) {
        dict[firstLetter].tabletter = realloc(dict[firstLetter].tabletter,
                                              (hash1 + 1) * sizeof(phash));

        if (dict[firstLetter].tabletter == NULL) {
            fprintf(stderr, "Pointer allocation error\n");
            return -1;
        }

        dict[firstLetter].lengthTabLetter = hash1 + 1;
    }

    for (int i = length1; i <= hash1; i++) {
        dict[firstLetter].tabletter[i].htab2 = NULL;
        dict[firstLetter].tabletter[i].lengthtab2 = 0;
    }

    int length2 = dict[firstLetter].tabletter[hash1].lengthtab2;

    if (length2 == 0) {
        dict[firstLetter].tabletter[hash1].lengthtab2 = 0;
        dict[firstLetter].tabletter[hash1].htab2 = malloc(sizeof(wordStruct *));

        if (dict[firstLetter].tabletter[hash1].htab2 == NULL) {
            fprintf(stderr, "Pointer allocation error\n");
            return -1;
        }
    }

    if (length2 <= hash2) {
        dict[firstLetter].tabletter[hash1].htab2 = realloc(dict[firstLetter].tabletter[hash1].htab2,
                                                           (hash2 + 1) * sizeof(wordStruct *));

        if (dict[firstLetter].tabletter[hash1].htab2 == NULL) {
            fprintf(stderr, "Pointer allocation error\n");
            return -1;
        }

        for (int i = length2; i <= hash2; i++)
            dict[firstLetter].tabletter[hash1].htab2[i] = NULL;

        dict[firstLetter].tabletter[hash1].lengthtab2 = hash2 + 1;
    }

    return 0;
}

int addWordIntoDictionary(dictionary dict, char *word, char *definition) {
    int hash1 = firstHashage(word);
    int hash2 = secondHashage(word);

    int i = 0;
    while (word[i] != '\0' && word[i] == '-')
        i++;

    if (word[i] == '\0')
        return -1;

    int firstLetter = word[i] - 65;

    if (rebuildStructure(dict, firstLetter, hash1, hash2) == -1)
        return -1;

    wordStruct **list = &dict[firstLetter].tabletter[hash1].htab2[hash2];

    wordStruct *sWord = createWord(word, definition);
    int res = addWordToList(list, sWord);

    if (res != 0)
        free(sWord);

    return res;
}

int fillDictionary(dictionary dict, char const *fileName) {
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return -1;
    }

    char c, *word, *definition;
    char buff[MAX_LENGTH];
    int i;

    printf("Please wait a few moments. (loading words ...)\n");

    c = fgetc(file);
    while (!feof(file) && c != '\n')
        c = fgetc(file);

    while (!feof(file)) {
        c = fgetc(file);
        i = 0;

        while (!feof(file) && c != ':' && i < MAX_LENGTH) {
            buff[i++] = c;
            c = fgetc(file);
        }

        buff[i] = '\0';

        word = malloc(sizeof(char) * i + 1);

        if (word == NULL) {
            fprintf(stderr, "Pointer allocation error\n");
            fclose(file);
            return -1;
        }
        word = strncpy(word, buff, i);
        word[i] = '\0';

        if (strcmp(word, "") != 0 && strcmp(word, "\n") != 0) {
            c = fgetc(file);
            i = 0;

            while (!feof(file) && c != '\n' && i < MAX_LENGTH) {
                buff[i++] = c;
                c = fgetc(file);
            }
            buff[i] = '\0';

            definition = malloc(sizeof(char) * i + 1);

            if (definition == NULL) {
                fprintf(stderr, "Pointer allocation error\n");
                fclose(file);
                return -1;
            }

            definition = strncpy(definition, buff, i);
            definition[i] = '\0';

            if (addWordIntoDictionary(dict, word, definition) != 0) {
                free(word);
                free(definition);
            }
        } else
            free(word);
    }

    fclose(file);
    return 0;
}

void freeDictionary(dictionary dict) {
    for (int i = 0; i < NUMBER_LETTERS; i++) {
        if (!dict[i].tabletter)
            continue;

        int length1 = dict[i].lengthTabLetter;

        for (int j = 0; j < length1; j++) {
            if (!dict[i].tabletter[j].htab2)
                continue;

            int length2 = dict[i].tabletter[j].lengthtab2;

            for (int k = 0; k < length2; k++) {
                if (!dict[i].tabletter[j].htab2[k])
                    continue;

                freeListWords(dict[i].tabletter[j].htab2[k]);
            }

            free(dict[i].tabletter[j].htab2);
        }

        free(dict[i].tabletter);
    }
}

int removeWordFromDictionary(dictionary dict, char *word) {
    if (word == NULL)
        return -1;

    int hash1 = firstHashage(word);
    int hash2 = secondHashage(word);

    int i = 0;
    while (word[i] != '\0' && word[i] == '-')
        i++;

    if (word[i] == '\0')
        return -1;

    int firstLetter = word[i] - 65;

    wordStruct *sWord = getWordFromDict(dict, word);

    if (sWord == NULL)
        return 1;

    wordStruct **list = &dict[firstLetter].tabletter[hash1].htab2[hash2];
    removeWordFromList(list, sWord);

    return 0;
}