#include "Dictionary.h"
#include "UIfunctions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {

	dictionary dict;

	if( start(dict, "Dictionary_ASCII.txt") != 0)
		exit(1);

	printf("\x1b[2J\x1b[1;1H");

	char *answer = malloc(sizeof(char) * 3);

	printf("\n\n");

	while(1) {

		displayMenuChoices();

		answer = fgets(answer, 3, stdin);

		if(answer[1] != '\n' && strlen(answer) >= 2) {
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF);
		}

		answer = trim(answer);

		printf("\n");

		if(strcmp(answer, "1") == 0) {
			
			wordStruct *sWord = searchWord(dict);
			
			if(sWord != NULL)
				printWord(sWord);
			else
				printf("\t Word not found.");
		}
		else if(strcmp(answer, "2") == 0) {
			
			int res = addWord(dict);
			if(res == 1)
				printf("\t Word already exist");
			else if(res == 0)
				printf("\t Word insertion done");
			else
				printf("\t Error during insertion");

		}
		else if(strcmp(answer, "3") == 0) {

			int res = removeWord(dict);
			if(res == 1)
				printf("\t Word does not exist");
			else if(res == 0)
				printf("\t Word deletion done");
			else
				printf("\t Error during deletion");
		}
		else if(strcmp(answer, "4") == 0)
			break;
		else
			printf("Invalide Choose ! Retry ");

		printf("\n\n  Press enter to continue ... \n");
		while(fgetc(stdin) != '\n');

		printf("\x1b[2J\x1b[1;1H");
	}

	free(answer);

	quit(dict);
	printf("\n");

	return 0;
}