#ifndef __DICTIONARY__H__
#define __DICTIONARY__H__

#include "word.h"

#define NUMBER_LETTERS 26

/*
	La structure du tableau des tetes de listes
	Elle continent un tableau de ptr vers mots
	ainsi que sa taille
*/
typedef struct _phash {
    wordStruct **htab2;
    int lengthtab2;

} phash;

/*
	La structure qui represente les mots qui commencent par une lettre
	Elle contient un tableau de la structure phash
	et sa taille
*/
typedef struct _tabletter {
    phash *tabletter;
    int lengthTabLetter;

} tabletter;

// Un dictionnaire est un tableau de 26 lettre d'alphabet
typedef tabletter dictionary[NUMBER_LETTERS];

// Fonction qui initialise le  dictionnaire
// Pour chaque case :
//  lengthTabLetter = 0
//  tabletter = NULL
void initDict(dictionary dict);

// Retourne l'adresse du mot donnee en argument
// NULL si il n'existe pas
wordStruct *getWordFromDict(dictionary dict, char *word);

// Charge le fichier de mots dans la strucutre du dictionnaire
// 0 succes
// -1 echec
int fillDictionary(dictionary dict, char const *fileName);

// Ajoute un mot dans le dictionnaire
// 0 succes
// -1 echec
int addWordIntoDictionary(dictionary dict, char *word, char *definition);

// Libere toute la structure du dictionnaire
void freeDictionary(dictionary dict);

// Realloue l'espace pour les nouveaux mots a ajouter
// 0 succes
// -1 echec
int rebuildStructure(dictionary dict, int firstLetter, int hash1, int hash2);

// Supprime un mot du dictionnaire
// -1 echec
// 0 succes
// 1 mot inexistant
int removeWordFromDictionary(dictionary dict, char *word);

#endif