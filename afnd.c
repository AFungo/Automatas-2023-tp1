#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STATES 3
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

int main (int argc, char *argv[]){

	struct AFN *a = malloc(sizeof(struct AFN));
	int states[] = {1,2,3};
	int alph[] = {0,1};
	int finalSt[] = {3};
	booleanArray delta[3][3] = { //       0           		1           
							/*1*/	{{true,false,false},{true,true,true}},
							/*2*/	{{false,false,false},{false,true,false}},
							/*3*/	{{false,true,true},{false,false,true}}
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
	
	//printf("%d",e);
}





//void entrada(String fileName);
//void salida(String fileName);        
//AFD AFNtoAFD(AFN afn)