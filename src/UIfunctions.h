#ifndef __UIFUNCTIONS__H__
#define __UIFUNCTIONS__H__

#include "Dictionary.h"
#include "word.h"

// Retourne le mot lit depuis le clavier
// retourne trim(input)
char *scanWord();

// Affiche le menu pour choisir l'operation a effectuee
void displayMenuChoices();

// Enleve les espaces au debut et a la fin des mots
// Et transforme les sequences d'espaces en un espace
// Et retourne le pointeur vers str
char *trim(char *str);

// Lance l'application
// init le dictionnaire
// 0 succes
// -1 echec
int start(dictionary dict, char *filename);

// Fonction d'ajout :
// Lit un mots en effectue son ajout si possible
// 0 succes
// -1 echec
// 1 Si mot existant
int addWord(dictionary dict);

// Fonction de recherche :
// Lit un mots
// Retourne l'adresse du mot
// NULL si il n'existe pas
wordStruct *searchWord(dictionary dict);

// Fonction de suppression :
// Lit un mots en effectue sa suppression si possible et retourne
// -1 echec
// 0 succes
// 1 mot inexistant
int removeWord(dictionary dict);

// Quitter l'application
// Libere toutes la structure du dictionnaire
void quit(dictionary dict);

#endif