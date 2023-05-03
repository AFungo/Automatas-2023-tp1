#include "afnd.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main (int argc, char *argv[]){

	AFN *a = malloc(sizeof(AFN));
	int states[] = {0,1,2};
	int alph[] = {0,1};
	int finalSt[] = {2};
	booleanArray delta[3][2] = { //       0           		1           
							/*0*/	{{false,true,false},{false,false,true}},
							/*1*/	{{false,false,true},{true,false,false}},
							/*2*/	{{true,false,false},{false,true,false}}
								}; 
	//printf("states %ld \n",sizeof(a->states)/sizeof(a->states[0]));
	memcpy(a->states, states, sizeof(int)*MAX_STATES);
	memcpy(a->alphabet, alph, sizeof(int)*ALPHABET_SIZE);
	memcpy(a->finalStates, finalSt, sizeof(int)*MAX_STATES);
	memcpy(a->delta, delta, sizeof(int)*MAX_STATES*ALPHABET_SIZE);
	a->initialState = 0;
	char string[] = "0";
	//printf("valorr: %d \n",(a->delta[string[0]][0][0]));
	//printf("%d\n" , a->initialState);
	//for (int i = 0; i < 3; i++)
	// {
	// 	for (int k = 0; k < 2; k++)
	// 	{
	// 		for (int j = 0; j < 3; j++)
	// 		{
	// 			printf("i= %d, j= %d, k= %d ",i,k,j);
	// 			printf("valor: %d \n",a->delta[i][k][j]);
	// 		}	
	//	}	
	//}
	
	bool e=pertence(a,string);
	
	if(e){
		printf("La cadena %s pertenece al lenguaje representado por el AFN",string);
	} else {
		printf("La cadena %s no pertenece al lenguaje representado por el AFN",string);
	}

	//printf("%d",e);
}