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
	addStateToStates(&automaton->states, state);
}

void addStateToStates(States *states, int state){
	bool isNewState = true;
	int i = 0;
	for(i; i < states->cant; i++){
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

struct Pair objectIsInMatriz(int m[matrixSize][MAX_STATES], int a[MAX_STATES]){	
	bool isIn=false;
	bool isValid = true;
	int pos;
	int i=0;
	int k;
	while (i<matrixSize && !isIn){
		k=0;
		isValid=true;
		while (k<MAX_STATES && isValid){
			if (m[i][k]==a[k]){
				k++;
			} else {
				isValid=false;
			}
			if (k==MAX_STATES && isValid){
				isIn=true;
				pos=i;
			}
		}
		i++;
	}
	struct Pair res = {isIn,pos};
	return res;
}

bool isInMatrix(int m[matrixSize][MAX_STATES], int a[MAX_STATES]){
	objectIsInMatriz(m,a).first;
}

int posInMatrix(int m[matrixSize][MAX_STATES], int a[MAX_STATES]){
	struct Pair p= objectIsInMatriz(m,a);
	if (p.first)
	{
		return p.second;
	} else {
		return -1;
	}
	
}

void addFinal(AFN *afn, AFD *afd, int matrix[matrixSize][MAX_STATES],int cantOfElem){
	for(int h = 0; h < cantOfElem; h++){
		for(int t = 0; t < MAX_STATES; t++){
			for(int i = 0; i < afn->finalStates.cant; i++){
				if(matrix[h][t] == afn->finalStates.states[i]){
					memcpy(afd->finalState[h], matrix[h], sizeof(afd->finalState[h]));
					break;
				}	
			}
		}
	}
}

void addState(int states[MAX_STATES], int matrix[matrixSize][MAX_STATES], int *cantOfElem){
	int idx = 0;
	bool validState = false;
	while(!validState && idx < MAX_STATES){
			if(states[idx] == -1){
				idx++;
			}else{
				validState = true;
			}
		}
		if(validState){
			memcpy(matrix[(*cantOfElem)], states, sizeof(int)*MAX_STATES);
			(*cantOfElem)++;
		}
}

int* closure(int states[MAX_STATES], booleanArray delta[MAX_STATES][ALPHABET_SIZE]){
	static int statesReached[MAX_STATES];
	memset(statesReached, -1, sizeof(statesReached));
	for(int j = 0; j < MAX_STATES; j++){
		if(states[j] != -1){
			statesReached[j] = states[j];
			for(int i = 0; i < MAX_STATES; i++){
				if(delta[statesReached[j]][0][i]==true){
					// verifico que al estaod que llego no llego otro estado revisado previamente
					if(statesReached[i] == -1){ 
						statesReached[i] = i;
					}
				}
			}
		}	
	}
	return statesReached;
}

//retorna un array con los nodos alcanzados por states, si por ningun valor de state
//hay una transicion entonces el array sera [-1,-1,-1...] dependiendo la cantidad de estados
//si hay una transicion, entonces retorna el valor del estado al que se llega
//ejemplo, states = {0,-1,2} (si hay un -1 representa un espacion en blanco el estado seria {0,2})
//el array retornado seria {0,1,-1} es decir que por el estado {0,2} se llega al estado {0,1-1} ({0,1})
int* move(int states[MAX_STATES], int alph, booleanArray delta[MAX_STATES][ALPHABET_SIZE]){
	static int statesReached[MAX_STATES];
	memset(statesReached, -1, sizeof(statesReached));
	for(int j = 0; j < MAX_STATES; j++){
		int k=0;
		if(states[j] != -1){
			for(int i = 0; i < MAX_STATES; i++){
				if(delta[states[j]][alph][i]==true){
					// verifico que al estaod que llego no llego otro estado revisado previamente
					if(statesReached[k] == -1){ 
						statesReached[k] = i;
					}
				}else {
					// verificar si no esta el valor de un estado que pudo ser añadido previemente
					// realizo estas verificaciones porque voy llenando un array de tamaño MAXSTATES
					if(statesReached[k] == -1){
						statesReached[k] = -1;
					}
				}
			k++;
		}
}
	}
	return statesReached;
}

int* initialClosure(int s, int alph, booleanArray delta[MAX_STATES][ALPHABET_SIZE]){
	static int arrOfstate[MAX_STATES];
	for(int i = 1; i < MAX_STATES; i++){
		if(delta[s][alph][i] == true){
				arrOfstate[i] = i;
		}else{
			arrOfstate[i] = -1;
		}
	}
	return arrOfstate;
}