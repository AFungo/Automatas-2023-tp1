#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STATES 10
#define FINAL_STATES 1
#define ALPHABET_SIZE 2
typedef bool booleanArray[MAX_STATES];

struct AFN{
	int states[MAX_STATES];
	int alphabet[ALPHABET_SIZE];
	booleanArray delta[MAX_STATES][ALPHABET_SIZE];
	int initialState;
	int finalStates[FINAL_STATES];
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
bool pertence(struct AFN t, char *chain){
	bool pA= pertenceAlph(t.alphabet,chain);
	if (pA){
		int actualState=t.initialState;
		int i=0;
		bool unlock=true;
		while (i<strlen(chain)&&unlock){
			int k=0;
			while (k<MAX_STATES){
				printf("%d",(t.delta[actualState][chain[i]])[k]);
				if ((t.delta[actualState][chain[i]])[k]){
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
				if(actualState=t.finalStates[i]){
					return true;
				}
			}
		}
		return false;		
	} else {
		return false;
	}
}

int main (int argc, char *argv[]){

	struct AFN *a = malloc(sizeof(struct AFN));
	int states[3] = {1,2,3};
	int alph[2] = {0,1};
	int finalSt[1] = {3};
	booleanArray delta[3][3] = { //       0           		1           
							/*1*/	{{true,false,false},{true,true,true},},
							/*2*/	{{false,false,false},{false,true,false},},
							/*3*/	{{false,true,true},{false,false,true},}
								}; 

	memcpy(a->states, states, sizeof(int)*3);
	memcpy(a->alphabet, alph, sizeof(int)*2);
	a->initialState = 1;
	memcpy(a->finalStates, finalSt, sizeof(int)*1);
	memcpy(a->delta, delta, sizeof(int)*3*3);
	//printf("%d \n",a->initialState);
	char string[] = "100101";
	bool e=pertence(*a,string);
	
	//printf("%d",e);
}





//void entrada(String fileName);
//void salida(String fileName);        
//AFD AFNtoAFD(AFN afn)