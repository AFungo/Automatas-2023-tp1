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
//precondition: MAXSTATES and ALPHABETSIZE has to be correct.
bool pertence(AFN *t, char *chain){
	bool pA= pertenceAlph(t->alphabet,chain);
	int ascii[2];
	int ichain;
	int k;
	if (pA){
		int actualState=t->initialState;
		int i=0;
		bool unlock=true;
		int cantStates=sizeof(t->states)/sizeof(t->states[0]);
		while (i<strlen(chain)&&unlock){
			k=0;
			while (k<cantStates){
				if ((t->delta[actualState][(int)chain[i]-48][k])){
					actualState=k;
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
			for (int i=0;i<MAX_STATES;i++){
				if(actualState==i && t->finalStates[i]==true){
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

void getMultipleTransitions(AFN *automaton, char *trans, int transitions[ALPHABET_SIZE]){
	
	trans = strtok(trans, ",");
	int symbol = atoi(trans);
	addSymbolToAutomaton(automaton, &symbol);
	transitions[symbol] = 1;
//	printf("S = %d, ", symbol);
	trans = strtok(NULL, ",");
	while(trans != NULL){
		symbol = atoi(trans);
//		printf("S = %d, ", symbol);
		addSymbolToAutomaton(automaton,&symbol);
		transitions[symbol] = 1;
		trans = strtok(NULL, ",");
	} 
/*	printf("\n trnsiciones:::");
	for(int i = 0; i<ALPHABET_SIZE;i++){
		if(transitions[i] == 1) printf("tras: %d,", i);
	}	
	printf("\n");*/
}

void addSymbolToAutomaton(AFN *automaton, int *symbol){
	if(*symbol == 33) *symbol = ALPHABET_SIZE - 1;//is lambda
	if(automaton->alphabet[*symbol] != 1) automaton->alphabet[*symbol] = 1;
}

void addInitialStateToAutomaton(AFN *automaton, int symbol){
	automaton->states[symbol] = 1;
	automaton->initialState = symbol;
}

AFN readAutomaton(char *fileName){

	FILE *file = fopen(fileName, "r");
	AFN automaton;
	automaton = initAutomaton(automaton);
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
			int transitions[ALPHABET_SIZE];

    		if(strstr(trans, ",")){//case if automaton have multiple transitions q3->q3 [label="1,2"];				
				getMultipleTransitions(&automaton, trans, transitions);
				//printf("\n trnsiciones:::");
				/*for(int i = 0; i<ALPHABET_SIZE;i++){
					if(transitions[i] == 1) printf("tras: %d,", i);
				}*/	
				//printf("\n");
			}else{                  //case only one transition q0->q1 [label="1"];
                int symbol = atoi(trans);
			//	printf("SYMBOLO UNICO = %d \n", symbol);
                addSymbolToAutomaton(&automaton, &symbol);
                transitions[symbol] = 1;
            }

    		// Extract the first and second state using strtok()
    		token = strtok(start, "-> ");
    		char *dep = token;
        	token = strtok(NULL, "-> ");
			char *arr = token;
			int departure = atoi(strtok(dep, "q"));
			int arrival = atoi(strtok(arr, "q"));
			
			//add states to automaton if no in yet
			if(automaton.states[departure] != 1) automaton.states[departure] = 1;
			if(automaton.states[arrival] != 1) automaton.states[arrival] = 1;
			
			//
			for(int i = 0; i < ALPHABET_SIZE; i++){
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
					if(j == ALPHABET_SIZE -1) fprintf(file, "q%d->q%d [label:\"!\"];\n", i, k);
					else fprintf(file, "q%d->q%d [label:\"%d\"];\n", i, k, j);
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
 	for(int i = 0; i<ALPHABET_SIZE-1;i++){
         if(automaton.alphabet[i] == 1)
			printf("%d, ", i);
	}
	if(automaton.alphabet[ALPHABET_SIZE-1] == 1) printf("!");
	printf("\nTransitions = \n");
    for(int i = 0; i<ALPHABET_SIZE;i++){          
		for(int j = 0; j <MAX_STATES;j++){
			for(int k = 0; k <MAX_STATES; k++){
				if(automaton.states[j] == 1 && automaton.alphabet[i] == 1  && automaton.delta[j][i][k] == true){ 
					if(i == ALPHABET_SIZE - 1) printf("q%d -> q%d - label: !\n", j, k);
					else printf("q%d -> q%d - label: %d\n", j, k, i);
				}
			}
		}
		
	}	
	
	
}

/*int* move(int state, int alph, booleanArray (*delta)[MAX_STATES][ALPHABET_SIZE]){
	static int states[MAX_STATES];
	for(int i = 0; i < MAX_STATES; i++){
		states[i] = -1;
	}	
	int j = 0;
	for(int i = 0; i < MAX_STATES; i++){
		if((*delta)[state][alph][i]==true){
			state[j] = i;
			j++;
		}
	}
	return states;
}

int[] clausuraLambdaArray(int[MAX_STATE] states, booleanArray delta){
	int states[MAX_STATES];

	for(int i = 0; i<MAX_STATES; i++){
		if(state[i]==1){
			int aux[] = clausuraLambda(i, delta);
			for(int j = 0; i<MAX_STATES; j++){
				if(aux[j]==1 && states[j] != 1){
					states[i] = 1;
				}
			}
		}
	}
}



int[] clausuraLambda(int estado, booleanArray (*delta)[MAX_STATES][ALPHABET_SIZE]){
    int lambda = MAX_STATE - 1;//DIGO QUIEN ES LAMBA
	int clausura[] = mover(state, lambda);//OBTENGO TODOS LOS ALCANZAVLES POR LAMBDA DEL ESTADO ACTUAL
	int explored[MAX_STATE];//DEFINO UN ARREGLO PARA GUARDAR LOS ESTADOS Q YA LOS MOVI POR LAMBDA
	explored[estado] = 1;// agrego el primer estado a los explorados
	while(!clausura.vacia()){//cuando no hay mas elementos para clausurar termina 
							//(seria hacer un metodo q todos los elemntos del arreglo != 1)
		for(int i = 0; i < MAX_STATE; i++){
			if(clausura[i]==1 && explored[i] != 1){//si es un estado sin explorar y alcanzado por lambda
				explored[i] = 1;//agrego el estado i a los explorados
				clausura[i] = 0;//lo saco de los elemtos que hay que clausurar
				int alcanzable[MAX_STATES] = mover(i, lambda, delta);//muevo el estados i por lambda
				for(int j = 0; j < MAX_STATE; j++){//agrego todos los estados que alcnaze por i a 
												  //la lista de clausura en caso de q no hayan sido explorados
					if(alcanzable[j] == 1 && explored[j] != 1){
						clausura[j] = 1;
					}
				}
			}
		}
	
	}
	return explored;
}

AFN AFNtoAFD(AFN automaton){
    
}
*/





