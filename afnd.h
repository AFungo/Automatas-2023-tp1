#ifndef AFND_H
#define AFND_H
#include <stdbool.h>
#define MAX_STATES 4
#define ALPHABET_SIZE 4
typedef bool booleanArray[MAX_STATES];

typedef struct{
	int states[MAX_STATES];
	int alphabet[ALPHABET_SIZE];//lambda = ALPHABET_SIZE - 1
	booleanArray delta[MAX_STATES][ALPHABET_SIZE];
	int initialState;
	int finalStates[MAX_STATES];
	int alphabet_size;
}AFN;

void addInitialStateToAutomaton(AFN *automaton, int symbol);
void getMulyipleTransitions(AFN *automaton, char *trans, int transitions[ALPHABET_SIZE]);
void addSymbolToAutomaton(AFN *automaton, int *symbol);
AFN readAutomaton(char *fileName);
void automatonToString(AFN automaton);
AFN initAutomaton(AFN automaton);
void writeAutomaton(char *fileName, AFN automaton);
bool pertenceAlph(int alph[], char *chain);
bool pertence(AFN *t, char *chain);
#endif
