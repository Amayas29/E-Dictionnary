#ifndef __WORD__H__
#define __WORD__H__

#define MAX_LENGTH 20000

/*
	La structure d'un mot
	ELle contient le mot, sa defintion
	et un ptr vers le mots suivant
*/
typedef struct _wordStruct wordStruct;
struct _wordStruct {
	
	char *word;
	char *definition;
	wordStruct *next;
};

// Creer un mot a partir des infos donnes en argument
// et retourne l'adresse du mot si il est creer
// NULL en cas d'erreur
wordStruct *createWord(char *word, char *definition);

// Effectue l'ajout d'un mot dans une liste
// 0 succes
// -1 echec
int addWordToList(wordStruct **listWords, wordStruct *word);

// Supprime un mot si il existe dans une liste de mots (change la liste)
void removeWordFromList(wordStruct **listWords, wordStruct *word);

// retourne l'adresse du mot si il existe dans la liste
// NULL sinon
wordStruct *getWordFromList(wordStruct *listWords, char *word);

// Affiche la structure de mot donne en argument
void printWord(wordStruct *word);

// Libere tous l'espace alloue pour une liste de mots
void freeListWords(wordStruct *listWords);

#endif