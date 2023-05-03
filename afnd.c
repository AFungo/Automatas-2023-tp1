#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STATES 3
#define FINAL_STATES 1
#define ALPHABET_SIZE 3
typedef bool booleanArray[MAX_STATES];
typedef int stateArray[MAX_STATES];

struct AFN{
	int states[MAX_STATES];
	int alphabet[ALPHABET_SIZE];
	booleanArray delta[MAX_STATES][ALPHABET_SIZE];
	int initialState;
	int finalStates[FINAL_STATES];
};

struct AFD{
	int states[MAX_STATES];
	int alphabet[ALPHABET_SIZE];
	int delta[MAX_STATES][ALPHABET_SIZE]; // int o bool?
	stateArray initialState;
	stateArray finalState[FINAL_STATES];
};

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

//in "1001011"
//out true or false depends of the AFN
bool pertence(struct AFN *t, char *chain){
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
			for (int i=0;i<FINAL_STATES;i++){
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

int* cantOfStates(){
	static int cantOfStates = 0;
	return &cantOfStates;
}

stateArray* clausuraInicial(int s, int alph, booleanArray (*delta)[MAX_STATES][ALPHABET_SIZE]){
	static stateArray arrOfstate[MAX_STATES];
	memset(arrOfstate,-1, sizeof(arrOfstate));
	arrOfstate[0][0] = s;
	int* p_cantOfStates = cantOfStates();
	for(int i = 1; i<MAX_STATES; i++){
		if(((*delta)[0][alph][i]==false) && (arrOfstate[0][i]==-1)){ // con  ==false funciona, pero con ==true no, no se actualiza la matriz?
			arrOfstate[0][i]=i+1;
		}
	}
	(*p_cantOfStates)++;
	return arrOfstate;
}

// stateArray* clausuraTransitiva(*stateArray state[MAX_STATES], int alph, booleanArray (*delta)[MAX_STATES][ALPHABET_SIZE]){
// 	for(int i = 0; i<MAX_STATES; i++){
// 		for(int j = 0; j<MAX_STATES; j++){
// 			if(state[i][j] != -1){
// 				(*delta)[state[i][j]][alph]
// 			}
// 		}
// 	}
// }


struct AFD* aFNtoAFD(struct AFN *a){
	struct AFD *d = malloc(sizeof(struct AFD));
	stateArray* initialSt = clausuraInicial(a->initialState, a->alphabet[0], &(a->delta));
	for (int i = 0; i < MAX_STATES; i++) {
    	for (int j = 0; j < MAX_STATES ; j++) {
        	printf("%d", *(initialSt[i] + j));
    	}
    	printf("\n");
	}


	
	return d;
	// for(int i = 0; i<=sizeof(initialSt); i++){
	// 	int k = 1;
	// 	for(int j = 0; j<=sizeof(initialSt[i]); j++){
	// 		int* newState = clausura(initialSt[i][j], a->alphabet[k],&(a->delta));
	// 		initialSt[i][j] 
	// 		k++;
	// 	}
	// }
	// int states[];
	// for(int c = 0; c<=cantOfStates; c++){
	// 	states[c] = c;
	// }
	// memcpy(d->states, states, sizeof(int)*cantOfStates);
	// d->initialState = 0;
	// memcpy(d->alphabet, a->alphabet, sizeof(int)*ALPHABET_SIZE);

	// return d;

}

int main (int argc, char *argv[]){

	struct AFN *a = malloc(sizeof(struct AFN));
	int states[] = {1,2,3};
	int alph[] = {-1,0,1};
	int finalSt[] = {3};
	booleanArray delta[3][3] = { //   		-1   				 0           		1           
							/*1*/	{{false,false,false},{true,false,false},{true,true,true}},
							/*2*/	{{false,false,false},{false,false,false},{false,true,false}},
							/*3*/	{{false,false,false},{false,true,true},{false,false,true}}
								}; 
	//printf("states %ld \n",sizeof(a->states)/sizeof(a->states[0]));
	memcpy(a->states, states, sizeof(int)*MAX_STATES);
	memcpy(a->alphabet, alph, sizeof(int)*ALPHABET_SIZE);
	memcpy(a->finalStates, finalSt, sizeof(int)*MAX_STATES);
	memcpy(a->delta, delta, sizeof(int)*MAX_STATES*ALPHABET_SIZE);
	a->initialState = 1;
	char string[] = "100101";
	//printf("valorr: %d \n",(a->delta[string[0]][0][0]));
	//printf("%d\n" , a->initialState);

	bool e=pertence(a,string);
	aFNtoAFD(a);
	
	//printf("%d",e);
}





//void entrada(String fileName);
//void salida(String fileName);     

	// for (int i = 0; i < MAX_STATES; i++) {
	// 	for (int j = 0; j < MAX_STATES; j++) {
	// 		for(int k = 0; k<MAX_STATES; k++){
	// 			printf("%s", a->delta[i][j][k] ? "true" : "false");
	// 		}
	// 	}
    // printf("\n"); // Salto de línea al final de cada fila
  	// }