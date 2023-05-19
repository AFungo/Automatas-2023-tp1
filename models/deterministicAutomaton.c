#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "deterministicAutomaton.h"

void initAFD(AFD *afd){
	memset(afd->finalStates.states,-1,sizeof(afd->finalStates));
	memset(afd->states.states,-1,sizeof(afd->states));
	memset(afd->alphabet.alphabet,-1,sizeof(afd->states));
	afd->states.cant = 0;
	afd->finalStates.cant = 0;
	afd->alphabet.cant = 0;
	for(int i = 0; i < MAX_STATES; i++){
		for(int j = 0; j < ALPHABET_SIZE; j++){
			afd->delta[i][j] = -1;
		}	
	}
}

void addNewDeltaToAFD(int departure, int arrival, int symbol, AFD *afd){
	int departureIndex = getStateIndex(afd->states, departure);
	int symbolIndex = getAlphabetIndex(afd->alphabet, symbol);
	afd->delta[departureIndex][symbolIndex] = arrival;
}

void addNewFinalStateToAFD(AFD *afd, int state){
	addStateToStates(&afd->finalStates, state);
}

void addStateToAFD(AFD *afd, int state){
	addStateToStates(&afd->states, state);
}

void addInitialStateToAFD(AFD *afd, int state){
	afd->initialState = state;
}
