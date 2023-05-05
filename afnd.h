#ifndef AFND_H
#define AFND_H
#include <stdbool.h>
#define MAX_STATES 3
#define ALPHABET_SIZE 3
typedef bool booleanArray[MAX_STATES];

typedef struct{
	int states[MAX_STATES];
	int alphabet[ALPHABET_SIZE];
	booleanArray delta[MAX_STATES][ALPHABET_SIZE];
	int initialState;
	int finalStates[MAX_STATES];
}AFN;

typedef struct{
	int states[pow(2,MAX_STATES)];
	int alphabet[ALPHABET_SIZE];
	int delta[MAX_STATES][ALPHABET_SIZE]; // int o bool?
	int initialState[MAX_STATES];
	int finalState[MAX_STATES];
}AFD;

AFN readAutomaton(char *fileName);
void automatonToString(AFN automaton);
AFN initAutomaton(AFN automaton);
void writeAutomaton(char *fileName, AFN automaton);
bool pertenceAlph(int alph[], char *chain);
bool pertence(AFN *t, char *chain);
void aFNtoAFD(AFN *a);

#endif
