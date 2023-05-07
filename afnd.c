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

int* cantOfStates(){
	static int cantOfStates = 0;
	return &cantOfStates;
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
						k++;
					}
				}else {
					// verificar si no esta el valor de un estado que pudo ser añadido previemente
					// realizo estas verificaciones porque voy llenando un array de tamaño MAXSTATES
					if(statesReached[k] == -1){
						statesReached[k] = -1;
					}
					k++;
				}
			}
}
	}
	return statesReached;
}

struct Pair matrixUtils(int m[MAX_STATES][MAX_STATES], int a[MAX_STATES]){	
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

bool isInMatrix(int m[MAX_STATES][MAX_STATES], int a[MAX_STATES]){
	matrixUtils(m,a).first;
}
int posInMatrix(int m[MAX_STATES][MAX_STATES], int a[MAX_STATES]){
	struct Pair p= matrixUtils(m,a);
	if (p.first)
	{
		return p.second;
	} else {
		return -1;
	}
	
}

void addFinal(AFN *afn, AFD *afd, int matrix[(int)pow(2,MAX_STATES)][(int)pow(2,MAX_STATES)],int cantOfElem){
	for(int i = 0; i < cantOfElem; i++){
		int j = 0;
		while(matrix[i][j] != -1){
			int state = matrix[i][j];
			if(isFinalState(*afn, state)){
				afd->delta[i][state] = true;
			}
		}
	}
}

void addState(int states[MAX_STATES], int matrix[(int)pow(2,MAX_STATES)][(int)pow(2,MAX_STATES)], int cantOfElem){
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
			memcpy(matrix[cantOfElem], states, sizeof(int)*MAX_STATES);
			cantOfElem++;
		}
}

AFD aFNtoAFD(AFN *afn){
	AFD *afd = malloc(sizeof(AFD));
	int matrix[(int)pow(2,MAX_STATES)][(int)pow(2,MAX_STATES)];
	int cantOfElem = 0;
	int* mover;
	int  pos;
	int aux; //verifica si aparecen estados nuevos
	memset(afd->states,-1,sizeof(afd->states));
	bool validState = false;
	memset(matrix, -1, sizeof(matrix));
	int* initialSt = initialClosure(afn->initialState, afn->alphabet.alphabet[0], (afn->delta));
	addState(initialSt, matrix,cantOfElem);
	int longitud = sizeof(initialSt) / sizeof(initialSt[0]);
	
	for(int j = 1; j < ALPHABET_SIZE; j++){
		mover = move(initialSt, j, (afn->delta));
		addState(mover, matrix, cantOfElem);
	}
	bool statesLeft = true;
	
	while(statesLeft){
		aux = cantOfElem;
		for(int i = 0; i < cantOfElem; i++){
			for(int alph = 1; alph < ALPHABET_SIZE; alph++){
				int* newState;
				newState = move(matrix[i], alph, afn->delta);
				if(!isInMatrix(matrix, newState)){
					addState(newState, matrix, cantOfElem);
					pos = posInMatrix(matrix, newState);
					afd->delta[i][alph] = pos;
				}
			}
		}
		if(cantOfElem == aux){
			statesLeft = false;
		}
	}
	
	for(int k = 0; k < cantOfElem; k++){
		afd->states[k] = k;
	}
	addFinal(afn, afd, matrix, cantOfElem);
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


int main(int argc, char const *argv[]){
		printf("%d", matrixSize);
		int matrix[matrixSize][(MAX_STATES)];
		memset(matrix,-1,sizeof(matrix));
		int array[MAX_STATES]={2,4,6};
		bool x;
		int pos;
		memcpy(matrix[4],array,sizeof(array));
		
		
		for (int i=0;i<matrixSize;i++){
			printf("\n");
			for (int k = 0; k<MAX_STATES; k++){
				printf("%d ", matrix[i][k]);
			}
		}
		printf("\n");
		
		
		x=isInMatrix(matrix,array);
		pos=posInMatrix(matrix,array);
		printf("\n");
		printf("%s\n", x == 1 ? "true" : "false");
		printf("\n");
		printf("Posicion: %d ",pos);
	}



