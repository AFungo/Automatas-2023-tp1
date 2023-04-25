#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STATES 10
#define ALPHABET_SIZE 2
typedef bool booleanArray[ALPHABET_SIZE];

struct AFN{
	int states[MAX_STATES];
	int alphabet[ALPHABET_SIZE];
	booleanArray delta[MAX_STATES][MAX_STATES];
	int initialState;
	int finalStates[MAX_STATES];
};


int main (int argc, char *argv[]){

	struct AFN *a = malloc(sizeof(struct AFN));

	a->states = {1,2,3};
	a->alphabet = {0,1};
	a->initialState = 1;
	a->finalStates = {3};
	a->delta = { //      1             2            3
			/*1*/	{{true,false},{true,true},{false,false}},
			/*2*/	{{false,false},{false,true},{true,true}},
			/*3*/	{{false,true},{false,false},{true,true}}
				};
	printf("%d",a->initialState);

}


//bool pertence(AFN a, int[] chain);
//void entrada(String fileName);
//void salida(String fileName);        
//AFD AFNtoAFD(AFN afn)