#include "afnd.h"
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]){

	AFN *a = malloc(sizeof(AFN));
	int states[] = {1,2,3};
	int alph[] = {0,1};
	int finalSt[] = {3};
	booleanArray delta[3][3] = { //       0           		1           
							/*1*/	{{true,false,false},{true,true,true}},
							/*2*/	{{false,false,false},{false,true,false}},
							/*3*/	{{false,true,true},{false,false,true}}
								}; 
	//printf("states %ld \n",sizeof(a->states)/sizeof(a->states[0]));
	memcpy(a->states, states, sizeof(int)*MAX_STATES);
	memcpy(a->alphabet, alph, sizeof(int)*ALPHABET_SIZE);
	memcpy(a->finalStates, finalSt, sizeof(int)*MAX_STATES);
	memcpy(a->delta, delta, sizeof(int)*MAX_STATES*ALPHABET_SIZE);
	a->initialState = 1;
	char string[] = "100101";
	//printf("valorr: %d \n",(a->delta[string[0]][0][0]));
	//printf("%d\n" , a->initialState);

	bool e=pertence(a,string);
	
	//printf("%d",e);
}