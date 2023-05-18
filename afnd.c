#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "afnd.h"
#include "utils.h"

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
//		printf("states: %d\n", afd.states.states[i]);	
		addStateToAutomaton(afn, afd.states.states[i]);
	}
	for(int i = 0;i<afd.alphabet.cant; i++){
//		printf("alphabet: %d\n", afd.alphabet.alphabet[i]);	
		addSymbolToAutomaton(afn, afd.alphabet.alphabet[i]);
	}
	for(int i = 0;i<afd.finalStates.cant; i++){
		//printf("finalStates: %d\n", afd.finalStates.states[i]);	
		addNewFinalStateToAutomaton(afn, afd.finalStates.states[i]);
	}
	for(int i = 0;i<afd.states.cant; i++){
		for(int j = 0;j<afd.alphabet.cant; j++){
		//	printf("state = %d \n", afd.delta[i][j]);
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
					if(symbol == 0) fprintf(file, "q%d->q%d [label:\"!\"];\n", departure, arrival);
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



	
	



