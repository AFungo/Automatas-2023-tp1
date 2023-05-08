#include "afnd.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main (int argc, char *argv[]){

	AFN *a = malloc(sizeof(AFN));
	States statesAFN;
    statesAFN.cant = 3;
    for(int i = 0; i < statesAFN.cant; i++){
        statesAFN.states[i] = i;
    }
	Alphabet alph;
    alph.cant = 3;
    for(int j = 0; j < alph.cant; j++){
        alph.alphabet[j] = j;
    }
	States finalSt;
    finalSt.cant = 1;
    finalSt.states[0] = 2;
	booleanArray delta[4][ALPHABET_SIZE] = { //			0					         1          		2           
                                            /*0*/	{{true,false,true,false},{false,true,true,false},{false,false,true,false}},
                                            /*1*/	{{false,true,false,false},{false,false,true,false},{true,false,false,false}},
                                            /*2*/	{{false,false,false,false},{true,true,false,true},{false,true,false,false}},
                                            /*3*/   {{false,false,false,true},{false,false,true,false},{false,false,false,false}}
                                                }; 
	//printf("states %ld \n",sizeof(a->states)/sizeof(a->states[0]));
	memcpy(a->states.states, statesAFN.states, sizeof(int)*MAX_STATES);
    a->states.cant = statesAFN.cant;
	memcpy(a->alphabet.alphabet, alph.alphabet, sizeof(int)*ALPHABET_SIZE);
    a->alphabet.cant = alph.cant;
	memcpy(a->finalStates.states, finalSt.states, sizeof(int)*MAX_STATES);
    a->finalStates.cant = finalSt.cant;
	memcpy(a->delta, delta, sizeof(int)*MAX_STATES*ALPHABET_SIZE);
    a->alphabet_size = alph.cant;
	a->initialState = 0;
	AFD *afd = malloc(sizeof(AFD));
    *afd = aFNtoAFD(a);
    for(int c = 0; c < MAX_STATES; c++){
        printf("%d",afd->initialState[c]);
    }
    printf("\n");;
     for(int d = 0; d < matrixSize; d++){
        printf("\n");
        for(int k = 0; k < MAX_STATES; k++){
            printf("%d",afd->finalState[d][k]);
        }
    }
    printf("\n");
    for(int y = 0; y < matrixSize; y++){
        printf("%d",afd->states[y]);
    }
    
}