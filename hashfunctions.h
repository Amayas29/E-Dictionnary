#ifndef __HASHFUNCTIONS__H__
#define __HASHFUNCTIONS__H__

/*
	Premieres Fonction de hashage qui genere 2-3 collisions
	A chaque fois on decale le resulat precedent de 2 positions
	et on ajoute le code de la lettre lu (code(A) = 0, code(B) = 1 ...)
	et on reccupere le modulo par rapport au nombre 171482

*/
int firstHashage(char *word);

/*
	Une secondefonctions pour separer les derniers collisions de la fonction precedente
	la sommes des code ASCII des lettres * leur positions
*/
int secondHashage(char *word);

#endif