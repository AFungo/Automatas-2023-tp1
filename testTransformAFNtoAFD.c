#include "afnd.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

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
	booleanArray delta[MAX_STATES][ALPHABET_SIZE] = { //			0					         1          		2           
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

    int deltaResult[MAX_STATES][ALPHABET_SIZE] ={{0,1,2},{0,1,3},{0,1,3},{0,1,3}};
    bool testDelta=true; 

    for (int i = 0; i < 4; i++){
        for (int k = 0; k < 3; k++){
            if(deltaResult[i][k]!=afd->delta[i][k]){
                testDelta=false;
            }
        }
        
    }
    bool testFinalSt=true;
    int finalStResult[MAX_STATES][MAX_STATES] ={{0,-1,2,-1},{0,1,2,3},{-1,1,2,-1},{0,1,2,-1}};
    for (int i = 0; i < 4; i++){
        for (int k = 0; k < 4; k++){
            if(finalStResult[i][k]!=afd->finalState[i][k]){
                testFinalSt=false;
            }
        }
        
    }

    bool testStates=true;
    int StatesResult[MAX_STATES][MAX_STATES] ={{0,-1,2,-1},{0,1,2,3},{-1,1,2,-1},{0,1,2,-1}};
    for (int i = 0; i < 4; i++){
        for (int k = 0; k < 4; k++){
            if(finalStResult[i][k]!=afd->finalState[i][k]){
                testFinalSt=false;
            }
        }
        
    }    
    printf("Resultado del test: %s",(testDelta&&testFinalSt&&testStates==true)? "true \n":"false \n");
}