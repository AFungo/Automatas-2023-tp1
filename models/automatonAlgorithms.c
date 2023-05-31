#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "noDeterministicAutomaton.h"
#include "../utils/utils.h"
#include "../utils/partitions.h"

bool pertence(AFN *automaton, char *chain){
	bool pA= true;//pertenceAlph(t->alphabet,chain);
	int ascii[2];
	int ichain;
	int k;
	int actualState=automaton->initialState;
	int i=0;
	bool unlock=true;
	int cantStates= automaton->states.cant;
	while (i<strlen(chain)&&unlock){
		k=0;
		while (k<cantStates){
			int actualStateIndex = getStateIndex(automaton->states, actualState);
			int symbolIndex = getAlphabetIndex(automaton->alphabet, (int)chain[i]-48);
			if ((automaton->delta[actualStateIndex][symbolIndex][k])){
				actualState = automaton->states.states[k];
				k=cantStates;
			} else {
				k++;
				if(k>=cantStates){
					unlock=false;
				}
			}
		}
		i++;
	}
	if(unlock){
		return isFinalState(*automaton, actualState);
	}
	return false;		
}

AFN AFDtoAFN(AFD afd){
	AFN *afn = malloc(sizeof(AFN));
	initAutomaton(afn);
	afn->initialState = afd.initialState;
	for(int i = 0;i<afd.states.cant; i++){
		addStateToAutomaton(afn, afd.states.states[i]);
	}
	for(int i = 0;i<afd.alphabet.cant; i++){
		addSymbolToAutomaton(afn, afd.alphabet.alphabet[i]);
	}
	for(int i = 0;i<afd.finalStates.cant; i++){
		addNewFinalStateToAutomaton(afn, afd.finalStates.states[i]);
	}
	for(int i = 0;i<afd.states.cant; i++){
		for(int j = 0;j<afd.alphabet.cant; j++){
			int index = getStateIndex(afn->states, afd.delta[i][j]);
			afn->delta[i][j][index] = true;
		}
	}
	return *afn;
}




AFD aFNtoAFD(AFN *afn){
	AFD *afd = malloc(sizeof(AFN));
	initAFD(afd);
	for(int k = 0; k < afn->alphabet.cant; k++){
		if(afn->alphabet.alphabet[k] != 0){//el symbolo no es lambda
			addNewSymbolToAlphabet(&afd->alphabet, afn->alphabet.alphabet[k]);	
		}
	}
	States matrix[matrixSize];
	int cantOfElem = 0;
	int  pos;
	int aux; //verifica si aparecen estados nuevos
	States *initialSt = initialClosure(afn->initialState, *afn);
	addInitialStateToAFD(afd, 0);
	addState(*initialSt, matrix, &(cantOfElem));
	addStateToAFD(afd, cantOfElem-1);
	if(haveFinalState(afn, *initialSt)) addStateToStates(&afd->finalStates, cantOfElem-1);
	int i = 0;
	while(aux!=cantOfElem){
		aux = cantOfElem;
		for(i; i < aux; i++){
			for(int alph = 0; alph < afn->alphabet.cant; alph++){
				States *newState = malloc(sizeof(States));
				int symbol = afn->alphabet.alphabet[alph];
				if(symbol != 0){//No es lambda
					newState = move(matrix[i], symbol, *afn);
					newState = closure(*newState, *afn);
					if(newState->cant>0){
						addState(*newState, matrix, &(cantOfElem));
						int newStateIndex = posInMatrix(matrix, *newState);
						addStateToStates(&afd->states, newStateIndex);
						if(haveFinalState(afn, *newState)) addNewFinalStateToAFD(afd, newStateIndex);
						addNewDeltaToAFD(getStateIndex(afd->states, i), newStateIndex, symbol, afd);
					}
				}	
			}
		}
		i = aux;
	}
	return *afd;
}


AFN readAutomaton(char *fileName){
	FILE *file = fopen(fileName, "r");
	AFN automaton;
	initAutomaton(&automaton);
	char line[1000];

	if(file == NULL){
		printf("Failed to open file\n");
	}	
	while(fgets(line, sizeof(line), file)){
		char *start = line;
		while(*start == ' ' || *start == '\t' || *start == '\r' || *start == '\n') start++;
       
		if(strcmp(start, "digraph") == 0) continue;

		else if(strstr(start, "inic->q") != NULL){
			int symbol = atoi(strtok(start, "inic->q"));
			addInitialStateToAutomaton(&automaton, symbol);
		}else if(strstr(start, "[label=")){

			char *token;	
    		char *label = strstr(start, "\"");
    		char *trans = strtok(label, "\"]");
			Alphabet transitions;
			initAlphabet(&transitions);

    		if(strstr(trans, ",")){//case if automaton have multiple transitions q3->q3 [label="1,2"];				
				getMultipleTransitions(&automaton, trans, &transitions);
			}else{                  //case only one transition q0->q1 [label="1"];
                int symbol = atoi(trans);
                addSymbolToAutomaton(&automaton, symbol);
                addNewSymbolToAlphabet(&transitions, symbol);
            }

    		// Extract the first and second state using strtok()
    		token = strtok(start, "-> ");
    		char *dep = token;
        	token = strtok(NULL, "-> ");
			char *arr = token;
			int departure = atoi(strtok(dep, "q"));
			int arrival = atoi(strtok(arr, "q"));
			
			//add states to automaton if no in yet
			addStateToAutomaton(&automaton, departure);
			addStateToAutomaton(&automaton, arrival);

			//
			for(int i = 0; i < transitions.cant; i++){
				int symbol = transitions.alphabet[i];
				addNewDeltaToAutomaton(&automaton, departure, arrival, symbol);		
			}
	
		}else if(strstr(start, "[shape=doublecircle]")){
			char *trans = strtok(start, "[shape=doublecircle]");
			int final = atoi(strtok(trans, "q"));
			addNewFinalStateToAutomaton(&automaton, final);
		}
		
	}
	return automaton;
	fclose(file);
}

void writeAutomaton(char *fileName, AFN automaton){
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Failed to open file\n");
    }
    fprintf(file, "digraph{\n");
    fprintf(file, "rankdir=LR;\n");
    fprintf(file, "inic[shape=point];\n");

    fprintf(file, "inic->q%d\n", automaton.initialState);
    
	for(int i = 0; i < automaton.states.cant; i++){
        for(int j = 0; j < automaton.alphabet.cant; j++){
            for(int k = 0; k < automaton.states.cant; k++){
                if(automaton.delta[i][j][k] == true){ 
					int departure = automaton.states.states[i];
					int arrival = automaton.states.states[k];
					int symbol = automaton.alphabet.alphabet[j];
					if(symbol == 0) fprintf(file, "q%d->q%d [label=\"!\"];\n", departure, arrival);
					else fprintf(file, "q%d->q%d [label=\"%d\"];\n", departure, arrival, symbol);
                }
            }
        }
    }
    for(int i = 0; i<automaton.finalStates.cant;i++){
		int finalState = automaton.finalStates.states[i];
        fprintf(file, "q%d[shape=doublecircle];\n", finalState);
    }
    fprintf(file, "}\n");
    fclose(file);
}




AFN *automatonUnion(AFN a, AFN b){

	AFN *automaton = malloc(sizeof(AFN));
	int stateNumber = 0;
	//add initial state to automaton
	addStateToAutomaton(automaton, stateNumber);
	addInitialStateToAutomaton(automaton, stateNumber);
	stateNumber++;
	int automatonStatesIndex[MAX_STATES];
	
	addSymbolToAutomaton(automaton, 0);//ad lambda
	
	//append a to the new automaton
	appendSymbolsToAFD(automaton, a);
	appendStatesToAFD(automaton, a, automatonStatesIndex, &stateNumber);
	appendDeltaToAFD(automaton, a, automatonStatesIndex);
	appendFinalStatesToAFD(automaton, a, automatonStatesIndex);

	//add transition by lambda between initial states of the new automaton and initial state of a
	int initialStateIndex = getStateIndex(a.states, a.initialState);
	addNewDeltaToAutomaton(automaton, 0, automatonStatesIndex[initialStateIndex], 0);

	int automatonBStatesIndex[MAX_STATES];

	//append b to the new automaton
	appendSymbolsToAFD(automaton, b);
	appendStatesToAFD(automaton, b, automatonBStatesIndex, &stateNumber);
	appendDeltaToAFD(automaton, b, automatonBStatesIndex);
	appendFinalStatesToAFD(automaton, b, automatonBStatesIndex);

	//add transition by lambda between initial states of the new automaton and initial state of b
	int bInitialStateIndex = getStateIndex(b.states, b.initialState);
	addNewDeltaToAutomaton(automaton, 0, automatonBStatesIndex[bInitialStateIndex], 0);

	return automaton;
}

AFN *automatonConcatenacion(AFN a, AFN b){
	AFN *automaton = malloc(sizeof(AFN));
	int stateNumber = 0;
	addSymbolToAutomaton(automaton, 0);//ad lambda
	int automatonStatesIndex[MAX_STATES];
	int automatonBStatesIndex[MAX_STATES];

	//append a to the new automaton but dont add final states
	appendSymbolsToAFD(automaton, a);
	appendStatesToAFD(automaton, a, automatonStatesIndex, &stateNumber);
	appendDeltaToAFD(automaton, a, automatonStatesIndex);

	//append b to the new automaton
	appendSymbolsToAFD(automaton, b);
	appendStatesToAFD(automaton, b, automatonBStatesIndex, &stateNumber);
	appendDeltaToAFD(automaton, b, automatonBStatesIndex);
	appendFinalStatesToAFD(automaton, b, automatonBStatesIndex);

	//add transition between final states of a and initial state of b
	States aFinalsStates = getAFDFinalStates(a);
	int bInitialStateIndex = getStateIndex(b.states, b.initialState);
	for(int i = 0; i < aFinalsStates.cant; i++){
		int finalStateIndex = getStateIndex(a.states, aFinalsStates.states[i]);
		addNewDeltaToAutomaton(automaton, automatonStatesIndex[finalStateIndex], automatonBStatesIndex[bInitialStateIndex], 0);
	}	
	return automaton;
}

AFN *automatonKlenneClausure(AFN a){
	AFN *automaton = malloc(sizeof(AFN));
	int stateNumber = 0;
	addSymbolToAutomaton(automaton, 0);
	int automatonStatesIndex[MAX_STATES];
	//add initial state to new automaton
	addStateToAutomaton(automaton, stateNumber);
	addInitialStateToAutomaton(automaton, stateNumber);
	stateNumber++;


	//append a to the new automaton but dont add final states		
	appendSymbolsToAFD(automaton, a);
	appendStatesToAFD(automaton, a, automatonStatesIndex, &stateNumber);
	appendDeltaToAFD(automaton, a, automatonStatesIndex);

	//add new final state to automaton
	addStateToAutomaton(automaton, stateNumber);
	addNewFinalStateToAutomaton(automaton, stateNumber);
	int finalState = stateNumber;
	stateNumber++;

	int initialStateIndex = getStateIndex(a.states, a.initialState);
	addNewDeltaToAutomaton(automaton, 0, automatonStatesIndex[initialStateIndex], 0);//add trasition by lambda between initial state and initial state of a
	addNewDeltaToAutomaton(automaton, automaton->initialState, finalState, 0);//add trasition by lambda between initial state and final state
	addNewDeltaToAutomaton(automaton, finalState, automaton->initialState, 0);//add trasition by lambda between final state and initial state

	//add trasition by lambda between final states of a and final state
	States aFinalsStates = getAFDFinalStates(a);
	for(int i = 0; i < aFinalsStates.cant; i++){
		int finalStateIndex = getStateIndex(a.states, aFinalsStates.states[i]);
		addNewDeltaToAutomaton(automaton, automatonStatesIndex[finalStateIndex], finalState, 0);
	}	
	return automaton;	
}



















States *kIndistinguibilidad(AFD afd){
/*	Partitions *partitions = malloc(sizeof(Partitions));
	States *newPartition = malloc(sizeof(States));
	cancatenateStates(newPartition, afd.states);
	removeStates(newPartition, afd.finalStates);
	addPartition(partitions, *newPartition);
	addPartition(partitions, afd.finalStates);
	bool changePartition = false;

	while(!changePartition){
		for(int i = 0; i < partitions->cant; i++){
			printf("PASEEEE%d\n", i);
			Partitions *newPartitions = malloc(sizeof(Partitions));
			States partition = partitions->partitions[i];
			for(int j = 0; j < partition.cant; j++){
				free(newPartition);
				newPartition = malloc(sizeof(States));
				int markedState = partition.states[j];
				addStateToStates(newPartition, markedState);
				for(int k = 0; k < partition.cant; k++){
					int unMarkedState = partition.states[k];
					if(equivalenceClassAreEquals(afd, markedState, unMarkedState, *partitions)){
						addStateToStates(newPartition, unMarkedState);
					}
				}
				addPartition(newPartitions, *newPartition);
			}
			if(!partitionsAreEquals(*partitions, *newPartitions)){
				printf("PASEEEE%d\n", i);
				free(partitions);
				printf("PASEEEE%d\n", i);
				*partitions = *newPartitions;
				printf("PASEEEE%d\n", i);
//				free(newPartitions);
				printf("PASEEEE%d\n", i);
			}else{
				changePartition = true;
			}
		}
	}
	partitionToString(*partitions);
//	partitionToString(*newPartitions);
*/}