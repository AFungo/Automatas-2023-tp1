#ifndef AFND_H
#define AFND_H
#include <stdbool.h>
#define MAX_STATES 3
#define ALPHABET_SIZE 2
typedef bool booleanArray[MAX_STATES];

typedef struct{
	int states[MAX_STATES];
	int cant;
}States;

typedef struct{
	int alphabet[ALPHABET_SIZE]; //lambda == 0
	int cant;
}Alphabet;

typedef struct{
	States states;
	Alphabet alphabet;
	booleanArray delta[MAX_STATES][ALPHABET_SIZE];
	int initialState;
	States finalStates;
	int alphabet_size;
}AFN;

AFN readAutomaton(char *fileName);
void writeAutomaton(char *fileName, AFN automaton);
bool pertence(AFN *t, char *chain);

#endif
