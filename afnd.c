#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
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
bool isFinalState(AFN afn, int state){
	for(int k = 0; k<MAX_STATES; k++){
		if(afn.delta[k]!=-1 && k == state){
			return true;
		}
	}
	return false;
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

void aFNtoAFD(AFN *afn){
	AFD *afd = malloc(sizeof(AFD));
	int matrix[(int)pow(2,MAX_STATES)][(int)pow(2,MAX_STATES)];
	int cantOfElem = 0;
	int* mover;
	int  pos;
	int aux; //verifica si aparecen estados nuevos
	memset(afd->states,-1,sizeof(afd->states));
	bool validState = false;
	memset(matrix, -1, sizeof(matrix));
	int* initialSt = initialClosure(afn->initialState, afn->alphabet[0], (afn->delta));
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
	return afd;
	

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

	// int main(int argc, char const *argv[]){
	// 	printf("%d", matrixSize);
	// 	int matrix[matrixSize][(MAX_STATES)];
	// 	memset(matrix,-1,sizeof(matrix));
	// 	int array[MAX_STATES]={2,4,6};
	// 	bool x;
	// 	int pos;
	// 	memcpy(matrix[4],array,sizeof(array));
		
		
	// 	for (int i=0;i<matrixSize;i++){
	// 		printf("\n");
	// 		for (int k = 0; k<MAX_STATES; k++){
	// 			printf("%d ", matrix[i][k]);
	// 		}
	// 	}
	// 	printf("\n");
		
		
	// 	x=isInMatrix(matrix,array);
	// 	pos=posInMatrix(matrix,array);
	// 	printf("\n");
	// 	printf("%s\n", x == 1 ? "true" : "false");
	// 	printf("\n");
	// 	printf("Posicion: %d ",pos);
	// }