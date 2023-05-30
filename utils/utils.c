#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"
#include "partitions.h"

bool isInMatrix(States m[matrixSize], States a, int matrizSize){
	for(int i=0; i<matrizSize; i++){
		if(statesAreEquals(m[i],a) || m[i].cant == -1){
			 return true;
		}
	}
	return false;
}

int posInMatrix(States m[matrixSize], States a){
	int i;
	for(i=0; i<matrixSize; i++){
		if(statesAreEquals(m[i],a)){
			return i;
		}
	}	
}

bool haveFinalState(AFN *afn, States state){
	for(int i = 0; i < afn->finalStates.cant; i++){
		for(int j = 0; j < state.cant; j++){
			if(afn->finalStates.states[i]==state.states[j]){
				return true;
			}
		}
	}
	return false;
}

void addFinalStateToMatrix(AFN *afn, AFD *afd, int matrix[matrixSize][MAX_STATES],int cantOfElem){
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
	if(states.cant > 0 && !isInMatrix(matrix, states, *cantOfElem)){
			matrix[(*cantOfElem)] =  states;
			(*cantOfElem)++;
	}
}

States *closure(States states, AFN afn){
	States *closureState = malloc(sizeof(States));
	cancatenateStates(closureState, states);
	int lamdaIndex = getAlphabetIndex(afn.alphabet, 0);
	int previousCant = 0;
	do{
		previousCant = closureState->cant;
		States *newState = move(*closureState, 0, afn);
		cancatenateStates(closureState, *newState);
	}while(previousCant != closureState->cant);
	return closureState;
}

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

void pintMAtrix(States matrix[matrixSize], int cant){
	for(int i = 0;i<cant; i++){
		States s = matrix[i];
		printStates(s);
	}
}


bool equivalenceClassAreEquals(AFD afd, int markedState, int unMarkedState, Partitions partitions){
/*	int markedStateIndex = getStateIndex(afd.states, markedState);
	int unMarkedStateIndex = getStateIndex(afd.states, unMarkedState);
	bool equivalenceClassesEquals = true;
	for(int i = 0; i < afd.alphabet.cant; i++){
		int symbol = afd.alphabet.alphabet[i];
		int markedArriveState = afd.delta[markedStateIndex][i];
		int unMarkedArriveState = afd.delta[unMarkedStateIndex][i];
		if(markedArriveState != unMarkedArriveState){
			int markedStatePartitionIndex = getPartitionIndexOfState(partitions, markedArriveState);
			int unMarkedStatePartitionIndex = getPartitionIndexOfState(partitions, unMarkedArriveState);
			if(markedStatePartitionIndex != unMarkedStatePartitionIndex) return false;
		}
	}
	return true;
*/}






