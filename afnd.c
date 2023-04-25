#include <stdio.h>

#define MAX_STATES 10
#define ALPHABET 2
typedef struct{
	int states[MAX_STATES];
	int alphabet[ALPHABET];
	int delta[MAX_STATES][MAX_STATES][ALPHABET];
	int initialState;
	int finalStates[MAX_STATES];
}automaton;



