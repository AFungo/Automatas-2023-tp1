#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"
#include "afnd.h"

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
		else	printf("%d, ", symbol);
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
					else printf("q%d -> q%d - label: %d\n", departure, arrival, symbol);
				}
			}
		}
		
	}	
	
	
}

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

void initAutomaton(AFN *automaton){
	memset(automaton->states.states,-1,sizeof(automaton->states.states));
	memset(automaton->finalStates.states,-1,sizeof(automaton->finalStates.states));
	memset(automaton->alphabet.alphabet,-1,sizeof(automaton->alphabet.alphabet));
	memset(automaton->delta,false,sizeof(automaton->delta));
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
	bool isNewState = true;
	int i = 0;
	for(i; i < automaton->states.cant; i++){
		if(automaton->states.states[i] == state){
			isNewState = false;
		}
	}
	if(isNewState){
		automaton->states.states[i] = state;
		automaton->states.cant++;
	}
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

void addNewDeltaToAutomaton(AFN *automaton, int departure, int arrival, int symbol){	
	int departureIndex = getStateIndex(automaton->states, departure);
	int arrivalIndex = getStateIndex(automaton->states, arrival);
	int symbolIndex = getAlphabetIndex(automaton->alphabet, symbol);

	automaton->delta[departureIndex][symbolIndex][arrivalIndex] = true;
}

int getStateIndex(States states, int state){
	for(int i = 0; i < states.cant; i++){
		if(states.states[i] == state) return i;
	}
	return -1;
}

int getAlphabetIndex(Alphabet alphabet, int symbol){
	for(int i = 0; i < alphabet.cant; i++){
		if(alphabet.alphabet[i] == symbol) return i;
	}
	return -1;
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

void initAlphabet(Alphabet *alphabet){
	for(int i = 0; i < ALPHABET_SIZE; i++){
		alphabet->alphabet[i] = -1;
	}
	alphabet->cant = 0;
}

bool isFinalState(AFN automaton, int s){
	for (int i=0; i < automaton.finalStates.cant; i++){
		if(automaton.finalStates.states[i] == s){
			return true;
		}
	}	
	return false;
}