#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "afnd.h"


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

bool pertence(AFN *t, char *chain){
	bool pA= pertenceAlph(t->alphabet,chain);
	if (pA){
		printf("initial state: %d \n",t->initialState);
		int actualState=t->initialState;
		int i=0;
		bool unlock=true;
		while (i<strlen(chain)&&unlock){
			int k=0;
			while (k<MAX_STATES){
				printf("as= %d, chain i= %d, k= %d ",actualState,chain[i]-48,k);
				printf("valor: %d \n",(t->delta[actualState-1][chain[i]-48][k]));
				if ((t->delta[actualState-1][chain[i]-48][k])){
					actualState=k;
					k=MAX_STATES;
				} else {
					k++;
					if(k>=MAX_STATES){
						unlock=false;
					}
				}
			}
			i++;
		}
		if(unlock){
			for (int i=0;i<MAX_STATES;i++){
				if(actualState=t->finalStates[i]){
					return true;
				}
			}
		}
		return false;		
	} else {
		return false;
	}
}

AFN initAutomaton(AFN automaton){
	
	for(int i = 0; i < MAX_STATES; i++){
		automaton.states[i] = 0;
	}
	
	for(int i = 0; i < MAX_STATES; i++){
		automaton.finalStates[i] = 0;
	}
	
	for(int i = 0; i < ALPHABET_SIZE; i++){
		automaton.alphabet[i] = 0;
	}
	
	for(int i = 0; i < MAX_STATES; i++){
		for(int j = 0; j < ALPHABET_SIZE; j++){
			for(int k = 0; k < MAX_STATES; k++){
				(automaton.delta[i][j])[k] = false;
			}
		}
	}
	return automaton;
}


AFN readAutomaton(char *fileName){
	FILE *file = fopen(fileName, "r");

	AFN automaton;
	
	automaton = initAutomaton(automaton);
	//automatonToString(automaton);

	if(file == NULL){
		printf("Failed to open file\n");
	}	
	char line[1000];
	while(fgets(line, sizeof(line), file)){
		char *start = line;
		while(*start == ' ' || *start == '\t' || *start == '\r' || *start == '\n') {
            start++;
        }

		if(strcmp(start, "digraph") == 0){

			continue;

		}else if(strstr(start, "inic->q") != NULL){

			char *line = strtok(start, "inic->q");
			int initState = atoi(line);
			automaton.states[initState] = 1;
			automaton.initialState = initState;

		}else if(strstr(start, "[label=")){

			char *token;
    		char *label = strstr(start, "\"");
    		char *trans = strtok(label, "\"]");
			int transitions[ALPHABET_SIZE];

    		if(strstr(trans, ",")){

				trans = strtok(trans, ",");
				
				if(automaton.alphabet[atoi(trans)] != 1) automaton.alphabet[atoi(trans)] = 1;
				
				transitions[atoi(trans)] = 1;
				trans = strtok(NULL, ",");
				
				while(trans != NULL){
					if(automaton.alphabet[atoi(trans)] != 1) automaton.alphabet[atoi(trans)] = 1;
					transitions[atoi(trans)] = 1;
					trans = strtok(NULL, ",");
				}

			}else{
				//printf("tokUnic = %d\n ", atoi(trans));
				if(automaton.alphabet[atoi(trans)] != 1) automaton.alphabet[atoi(trans)] = 1;
				transitions[atoi(trans)] = 1;
			}
    		// Extract the first and second state using strtok()
    		token = strtok(start, "-> ");
    		char *dep = token;
        	token = strtok(NULL, "-> ");
			char *arr = token;
			int departure = atoi(strtok(dep, "q"));
			int arrival = atoi(strtok(arr, "q"));
			//printf("Departure: %d, Arrival: %d\n", departure, arrival);
			if(automaton.states[departure] != 1) automaton.states[departure] = 1;
			if(automaton.states[arrival] != 1) automaton.states[arrival] = 1;
			for(int i = 0; i < ALPHABET_SIZE; i++){	
				//printf("dep: %d, arr: %d, trans: %d\n", departure, arrival, transitions[i]);
				if(transitions[i] == 1){
					automaton.delta[departure][i][arrival] = true;	
					transitions[i] = 0;
				}
			}	
		}else if(strstr(start, "[shape=doublecircle]")){
			char *trans = strtok(start, "[shape=doublecircle]");
			int final = atoi(strtok(trans, "q"));
			automaton.finalStates[final] = 1;
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
    
	for(int i = 0; i < MAX_STATES; i++){
        for(int j = 0; j < ALPHABET_SIZE; j++){
            for(int k = 0; k < MAX_STATES; k++){
                if(automaton.states[i] == 1 && automaton.alphabet[j] == 1  && automaton.delta[i][j][k] == true){ 
					fprintf(file, "q%d->q%d [label:\"%d\"];\n", i, k, j);
                }
            }
        }
    }
    for(int i = 0; i<MAX_STATES;i++){
         if(automaton.finalStates[i]==1) fprintf(file, "q%d[shape=doublecircle];\n", i);
    }
    fprintf(file, "}\n");
    fclose(file);
}


void automatonToString(AFN automaton){
	printf("initial state = %d\n", automaton.initialState);
	printf("States = ");
	for(int i = 0; i<MAX_STATES;i++){
		if(automaton.states[i]==1) printf("%d, ", i);
	}
	printf("\nFinal states = ");
    for(int i = 0; i<MAX_STATES;i++){
         if(automaton.finalStates[i]==1) printf("%d, ", i);
    }

	printf("\nAlphabet = ");
 	for(int i = 0; i<ALPHABET_SIZE;i++){
         if(automaton.alphabet[i]) printf("%d, ", i);
    }
	printf("\nTransitions = \n");
    for(int i = 0; i<ALPHABET_SIZE;i++){          
		for(int j = 0; j <MAX_STATES;j++){
			for(int k = 0; k <MAX_STATES; k++){
				if(automaton.states[j] == 1 && automaton.alphabet[i] == 1  && automaton.delta[j][i][k] == true){ 
					printf("q%d -> q%d - label: %d\n", j, k, i);
				}
			}
		}
		
	}	
	
	
}
