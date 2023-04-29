#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STATES 10
#define ALPHABET_SIZE 2
typedef bool booleanArray[MAX_STATES];

struct AFN{
	int states[MAX_STATES];
	int alphabet[ALPHABET_SIZE];
	booleanArray delta[MAX_STATES][ALPHABET_SIZE];
	int initialState;
	int finalStates[MAX_STATES];
};

bool pertence(struct AFN t, char *chain){
	printf("%d \n",strlen(chain));
	int i=0;
	bool alph=true;
	int k;
	while (i < strlen(chain) && alph){
		printf("alph is %d \n",alph);
		alph=false;
		k=0;
		while (k<ALPHABET_SIZE && !alph){
			printf("chain en 'i' is %d and alph in 'k' is %d \n",(int)chain[i],t.alphabet[k]);
			if((int)chain[i]==t.alphabet[k]){ //esta comparando el codigo ascii de chain[i] con el caracter de t.alphabet, por ejemplo 49, donde 49 es el ascii de "1", con "1"
				alph=true;
			}
		k++;
		}
	i++;		
	}
	return alph;
}

int main (int argc, char *argv[]){

	struct AFN *a = malloc(sizeof(struct AFN));
	int states[3] = {1,2,3};
	int alph[2] = {0,1};
	int finalSt[1] = {3};
	booleanArray delta[3][3] = { //       0           		1           
							/*1*/	{{true,false,false},{true,true,true},},
							/*2*/	{{false,false,false},{false,true,false},},
							/*3*/	{{false,true,true},{false,false,true},}
								}; 

	memcpy(a->states, states, sizeof(int)*3);
	memcpy(a->alphabet, alph, sizeof(int)*2);
	a->initialState = 1;
	memcpy(a->finalStates, finalSt, sizeof(int)*1);
	memcpy(a->delta, delta, sizeof(int)*3*3);
	printf("%d \n",a->initialState);
	char string[] = "100101\0";
	bool e=pertence(*a,string);
	
	printf("%d",e);
}





//void entrada(String fileName);
//void salida(String fileName);        
//AFD AFNtoAFD(AFN afn)