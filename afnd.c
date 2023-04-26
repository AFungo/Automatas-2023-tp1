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
	printf("%d",a->initialState);

}


//bool pertence(AFN a, int[] chain);
//void entrada(String fileName);
//void salida(String fileName);        
//AFD AFNtoAFD(AFN afn)