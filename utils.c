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
	//memset(automaton->delta,0,sizeof(automaton->delta));
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

void addStateToStates(States *states, int state){
	bool isNewState = true;
	int i = 0;
	for(i = 0; i < states->cant; i++){
		if(states->states[i] == state){
			isNewState = false;
		}
	}
	if(isNewState){
		states->states[i] = state;
		states->cant++;
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

// struct Pair objectIsInMatriz(States m[matrixSize], States a){	
// 	bool isIn=true;
// 	bool isValid = true;
// 	int pos;
// 	int i=0;
// 	int k;
// 	while (i<matrixSize && !isIn){
// 		k=0;
// 		isValid=true;
// 		States s = m[i];
// 		for(int j=0; j<s.cant; j){
// 			for(int k=0; k<a.cant; k++){
// 				if(getStateIndex)
// 			}
// 		}
// 		i++;
// 	}
// 	struct Pair res = {isIn,pos};
// 	return res;
// }


bool isInMatrix(States m[matrixSize], States a, int matrizSize){
	for(int i=0; i<matrizSize; i++){
		if(statesAreEquals(m[i],a) || m[i].cant == -1){
			// printf("igual\n\n\n");
			 return true;
		}
	}
//	 printf("distinto\n\n\n");
	return false;
}

int posInMatrix(States m[matrixSize], States a){
	int i;
	for(i=0; i<matrixSize; i++){
	//	 printf("M = ");
	//	 printStates(m[i]);
	//	 printf("A = ");
	//	 printStates(a);
		if(statesAreEquals(m[i],a)){
	//		printf("pos in matrix %d\n", i);
			return i;
		}
	}	
}

bool statesAreEquals(States a,States b){
	if(a.cant != b.cant) return false;
	for(int i=0; i<a.cant; i++){
		bool isIn = false;
		for(int j=0; j<b.cant; j++){
	//		printf("a = %d- b = %d \n", a.states[i], b.states[j]);
			if(a.states[i] == b.states[j]){
				isIn = true;
				j = b.cant+1;
			}
		}
		if(!isIn){
//		 	printf("Distintos estados\n");
			return false;
		
		}
	}
 //	printf("Iguales estados\n");
	return true;
}


bool haveFinalState(AFN *afn, States state){
	//printf("cantidad estados encontrados = %d \n", state.cant);
	for(int i = 0; i < afn->finalStates.cant; i++){
		for(int j = 0; j < state.cant; j++){
		//	printf("final = %d, encontrado = %d condicion = %d\n", afn->finalStates.states[i], state.states[j], afn->finalStates.states[i]==state.states[j]);
			if(afn->finalStates.states[i]==state.states[j]){
				return true;
			}
		}
	}
	return false;
}

void addFinal(AFN *afn, AFD *afd, int matrix[matrixSize][MAX_STATES],int cantOfElem){
	for(int h = 0; h < cantOfElem; h++){
		for(int t = 0; t < MAX_STATES; t++){
			for(int i = 0; i < afn->finalStates.cant; i++){
				if(matrix[h][t] == afn->finalStates.states[i]){
					addStateToStates(&afd->states, h);
					break;
				}	
			}
		}
	}
}

void addState(States states, States matrix[matrixSize], int *cantOfElem){
	// printf("nex founded %d\n", states.cant);
	if(states.cant > 0 && !isInMatrix(matrix, states, *cantOfElem)){
			matrix[(*cantOfElem)] =  states;
			(*cantOfElem)++;
	}
}

void cancatenateStates(States *state, States newState){
	for(int i = 0; i <newState.cant; i++){
		//printStates(*state);
		//printStates(newState);
		addStateToStates(state, newState.states[i]);
	}
}

States *closure(States states, AFN afn){
	States *closureState = malloc(sizeof(States));
	printStates(*closureState);
	cancatenateStates(closureState, states);
	printStates(*closureState);
	int lamdaIndex = getAlphabetIndex(afn.alphabet, 0);
	int previousCant = 0;
	//printf("\n\n\n\n ESACA \n");
	do{
		previousCant = closureState->cant;
		States *newState = move(*closureState, 0, afn);

		cancatenateStates(closureState, *newState);
	}while(previousCant != closureState->cant);
	//printf("\n\n\n\n");
	return closureState;
/*	for(int j = 0; j < states->cant; j++){
		int departureState = states->states[j];
		int departueIndex = getStateIndex(afn.states, departureState);
		for(int i = 0; i < afn.states.cant; i++){
			if(afn.delta[departueIndex][lamdaIndex][i]==true){
				int arrivalState = afn.states.states[i];
				addStateToStates(states, arrivalState);
			}
		}
	}
*/
}

//retorna un array con los nodos alcanzados por states, si por ningun valor de state
//hay una transicion entonces el array sera [-1,-1,-1...] dependiendo la cantidad de estados
//si hay una transicion, entonces retorna el valor del estado al que se llega
//ejemplo, states = {0,-1,2} (si hay un -1 representa un espacion en blanco el estado seria {0,2})
//el array retornado seria {0,1,-1} es decir que por el estado {0,2} se llega al estado {0,1-1} ({0,1})
States *move(States states, int alph, AFN afn){
	States *statesReached = malloc(sizeof(States));
	memset(statesReached->states, -1, sizeof(statesReached));
	int symbolIndex = getAlphabetIndex(afn.alphabet, alph);
	if(symbolIndex == -1) return statesReached;
	for(int j = 0; j < states.cant; j++){
		for(int i = 0; i < afn.states.cant; i++){
			int departureIndex = getStateIndex(afn.states, states.states[j]);
			int arrivalState = afn.states.states[i];
			if(afn.delta[departureIndex][symbolIndex][i]==true){
				addStateToStates(statesReached, arrivalState);
			}
		}
	}
	return statesReached;
}

States *initialClosure(int s, AFN afn){
	States *arrOfstate = malloc(sizeof(States));
	addStateToStates(arrOfstate, s);
	return closure(*arrOfstate, afn);
}


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


void printStates(States s){
	printf("[");
	for(int j = 0;j<s.cant; j++){
		printf("%d,", s.states[j]);
	}
	printf("]\n");
}

void pintMAtrix(States matrix[matrixSize], int cant){
	for(int i = 0;i<cant; i++){
		States s = matrix[i];
		printStates(s);
	}
}

void addNewDeltaToAFD(int departure, int arrival, int symbol, AFD *afd){
	printf("AGREGUE UN DELTA BRO\n");
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
