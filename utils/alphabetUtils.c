#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "alphabetUtils.h"

bool pertenceAlph(int alph[], char *chain){
	int i=0;
	bool a=true;
	int k;
	char ascii[2];
	while (i < strlen(chain) && a){
		a=false;
		k=0;
		while (k<ALPHABET_SIZE && !a){
			sprintf(ascii, "%d", alph[k]);
			if(chain[i]==(int)ascii[0]){
				a=true;
			}
		k++;
		}
	i++;		
	}
	return a;
}

bool symbolBelongsToAlphabet(Alphabet alphabet, int symbol){	
	for(int i = 0; i < alphabet.cant; i++){
		if(alphabet.alphabet[i] == symbol) return true;
	}
	return false;
}

void addNewSymbolToAlphabet(Alphabet *alphabet, int symbol){
	if(symbol == 33) symbol = 0;//is lambda
	bool isNewSymbol = true;
	int i = 0;
	for(i; i < alphabet->cant; i++)
		if(alphabet->alphabet[i] == symbol){
			isNewSymbol = false;
		}
	if(isNewSymbol){
		alphabet->alphabet[i] = symbol;
		alphabet->cant++;
	}
}

int getAlphabetIndex(Alphabet alphabet, int symbol){
	for(int i = 0; i < alphabet.cant; i++){
		if(alphabet.alphabet[i] == symbol) return i;
	}
	return -1;
}

void initAlphabet(Alphabet *alphabet){
	for(int i = 0; i < ALPHABET_SIZE; i++){
		alphabet->alphabet[i] = -1;
	}
	alphabet->cant = 0;
}

int parseCharToInt(char symbol){
	return (int) symbol;
}

char parseIntToChar(int symbol){
	return (char)symbol;
}

void printAlphabetChar(Alphabet alphabet){
	printf("Alphabet -- cant = %d \n", alphabet.cant);
	for(int i=0; i<alphabet.cant; i++){
		printf("%d - ", alphabet.alphabet[i]);
	}
}