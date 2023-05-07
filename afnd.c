#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "afnd.h"
#include "utils.h"




//precondition: MAXSTATES and ALPHABETSIZE has to be correct.
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
					else fprintf(file, "q%d->q%d [label:\"%d\"];\n", departure, arrival, symbol);
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







