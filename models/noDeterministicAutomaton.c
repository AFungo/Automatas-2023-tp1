#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "noDeterministicAutomaton.h"

void automatonToString(AFN automaton){
	printf("initial state = %d\n", automaton.initialState);
	printf("States = ");
	for(int i = 0; i<automaton.states.cant;i++){
		int state = automaton.states.states[i];
		printf("%d, ", state);
	}
	printf("\nFinal states = ");
    for(int i = 0; i<automaton.finalStates.cant;i++){
        int state = automaton.finalStates.states[i];
        printf("%d, ", state);
    }

	printf("\nAlphabet = ");

 	for(int i = 0; i<automaton.alphabet.cant;i++){
     	int symbol = automaton.alphabet.alphabet[i];
     	if(automaton.alphabet.alphabet[i] == 0) printf("!");	
		else	printf("%c, ", (char)symbol);
	}
	printf("\nTransitions = \n");
	for(int i = 0; i<automaton.alphabet.cant;i++){          
		for(int j = 0; j <automaton.states.cant;j++){
			for(int k = 0; k <automaton.states.cant; k++){
				int departure = automaton.states.states[j];
				int arrival = automaton.states.states[k];
				int symbol = automaton.alphabet.alphabet[i];
				if(automaton.delta[j][i][k] == true){ 
					if(symbol == 0) printf("q%d -> q%d - label: !\n", departure, arrival);
					else printf("q%d -> q%d - label: %c\n", departure, arrival, (char)symbol);
				}
			}
		}
		
	}	
	
	
}

void initAutomaton(AFN *automaton){
	memset(automaton->states.states,-1,sizeof(automaton->states.states));
	memset(automaton->finalStates.states,-1,sizeof(automaton->finalStates.states));
	memset(automaton->alphabet.alphabet,-1,sizeof(automaton->alphabet.alphabet));
	for(int i = 0;i<MAX_STATES;i++){
		for(int j = 0; j < ALPHABET_SIZE; j++){
			for(int k = 0;k<MAX_STATES;k++){
				automaton->delta[i][j][k] = 0;
			}
		}
	}
	automaton->states.cant = 0;
	automaton->finalStates.cant = 0;
	automaton->alphabet.cant = 0;
}

void getMultipleTransitions(AFN *automaton, char *trans, Alphabet *transitions){
	
	trans = strtok(trans, ",");
	int symbol = atoi(trans);
	addSymbolToAutomaton(automaton, symbol);
	addNewSymbolToAlphabet(transitions, symbol);
	trans = strtok(NULL, ",");
	while(trans != NULL){
		symbol = atoi(trans);
		addSymbolToAutomaton(automaton, symbol);
		addNewSymbolToAlphabet(transitions, symbol);
		trans = strtok(NULL, ",");
	} 
}

void addSymbolToAutomaton(AFN *automaton, int symbol){
	addNewSymbolToAlphabet(&automaton->alphabet, symbol);
}

void addInitialStateToAutomaton(AFN *automaton, int state){
	addStateToAutomaton(automaton, state);
	automaton->initialState = state;
}

void addStateToAutomaton(AFN *automaton, int state){
	addStateToStates(&automaton->states, state);
}

void addNewDeltaToAutomaton(AFN *automaton, int departure, int arrival, int symbol){	
	int departureIndex = getStateIndex(automaton->states, departure);
	int arrivalIndex = getStateIndex(automaton->states, arrival);
	int symbolIndex = getAlphabetIndex(automaton->alphabet, symbol);
	automaton->delta[departureIndex][symbolIndex][arrivalIndex] = true;
}

void addNewFinalStateToAutomaton(AFN *automaton, int state){
	bool isNewFinalState = true;
	int i = 0;
	for(i; i < automaton->finalStates.cant; i++){
		if(automaton->finalStates.states[i] == state){
			isNewFinalState = false;
		}
	}
	if(isNewFinalState){
		automaton->finalStates.states[i] = state;
		automaton->finalStates.cant++;
	}	
}

bool isFinalState(AFN automaton, int s){
	for (int i=0; i < automaton.finalStates.cant; i++){
		if(automaton.finalStates.states[i] == s){
			return true;
		}
	}	
	return false;
}

void appendSymbolsToAFN(AFN *automaton, AFN b){
	for(int symbolIndex = 0; symbolIndex < b.alphabet.cant; symbolIndex++){
		addSymbolToAutomaton(automaton, b.alphabet.alphabet[symbolIndex]);		
	}	
}	
	
void appendStatesToAFN(AFN *automaton, AFN b, int statesIndex[MAX_STATES], int *stateNumber){
	for(int stateIndex = 0; stateIndex < b.states.cant; stateIndex++){
		addStateToAutomaton(automaton, *stateNumber);
		statesIndex[stateIndex] = *stateNumber;
		(*stateNumber)++;
	}
}

void appendDeltaToAFN(AFN *automaton, AFN b, int statesIndex[MAX_STATES]){
	for(int departureIndex = 0; departureIndex < b.states.cant; departureIndex++){
		for(int symbolIndex = 0; symbolIndex < b.alphabet.cant; symbolIndex++){
			for(int arrivalIndex = 0; arrivalIndex < b.states.cant; arrivalIndex++){
				if(b.delta[departureIndex][symbolIndex][arrivalIndex] == true){
					int symbol = b.alphabet.alphabet[symbolIndex];
					addNewDeltaToAutomaton(automaton, statesIndex[departureIndex], statesIndex[arrivalIndex], symbol);
				}	
			}
		}
	}	
}

void appendFinalStatesToAFN(AFN *automaton, AFN b, int statesIndex[MAX_STATES]){
	for(int i = 0; i < b.finalStates.cant; i++){
		int finalStateIndex = getStateIndex(b.states, b.finalStates.states[i]);
		int finalState = statesIndex[finalStateIndex];
		addNewFinalStateToAutomaton(automaton, finalState);
	}	
}

States getAFNFinalStates(AFN automaton){
	States *finalStates = malloc(sizeof(States));
	for(int i = 0; i < automaton.finalStates.cant; i++){
		addStateToStates(finalStates, automaton.finalStates.states[i]);
	}
	return *finalStates;
}

AFN *createAutomaton(int symbol){
	AFN *afn = malloc(sizeof(AFN));
	addSymbolToAutomaton(afn, symbol);
	addStateToAutomaton(afn, 0);
	addStateToAutomaton(afn, 1);
	addInitialStateToAutomaton(afn, 0);
	addNewDeltaToAutomaton(afn, 0, 1, symbol);
	addNewFinalStateToAutomaton(afn, 1);
	return afn;
}