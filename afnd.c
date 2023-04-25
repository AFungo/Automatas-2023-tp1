#include <stdio.h>
#include <stdbool.h>

#define MAX_STATES 10
#define ALPHABET_SIZE 2
typedef bool booleanArray[ALPHABET_SIZE];

struct{
	int states[MAX_STATES];
	int alphabet[ALPHABET_SIZE];
	booleanArray delta[MAX_STATES][MAX_STATES];
	int initialState;
	int finalStates[MAX_STATES];
}AFN;




int main (int argc, char *argv[]){
	
}


//bool pertence(AFN a, int[] chain);
//void entrada(String fileName);
//void salida(String fileName);        
//AFD AFNtoAFD(AFN afn)