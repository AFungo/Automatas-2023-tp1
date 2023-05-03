#ifndef AFND_H
#define AFND_H
#include <stdbool.h>
#define MAX_STATES 3
#define ALPHABET_SIZE 2
typedef bool booleanArray[MAX_STATES];

typedef struct{
	int states[MAX_STATES];
	int alphabet[ALPHABET_SIZE];
	booleanArray delta[MAX_STATES][ALPHABET_SIZE];
	int initialState;
	int finalStates[MAX_STATES];
}AFN;

struct AFD{
	int states[MAX_STATES];
	int alphabet[ALPHABET_SIZE];
	int delta[MAX_STATES][ALPHABET_SIZE]; // int o bool?
	stateArray initialState;
	stateArray finalState[MAX_STATES];
};

AFN readAutomaton(char *fileName);
void automatonToString(AFN automaton);
AFN initAutomaton(AFN automaton);
void writeAutomaton(char *fileName, AFN automaton);
bool pertenceAlph(int alph[], char *chain);
bool pertence(AFN *t, char *chain);
#endif
