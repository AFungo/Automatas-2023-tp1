#include <stdio.h>
#include <stdbool.h>

#define MAX_STATES 10
#define ALPHABET_SIZE 2
typedef bool booleanArray[ALPHABET_SIZE];

typedef struct{
	int states[MAX_STATES];
	int alphabet[ALPHABET_SIZE];
	booleanArray delta[MAX_STATES][MAX_STATES];
	int initialState;
	int finalStates[MAX_STATES];
}automaton;



int main (int argc, char *argv[]){
	
}