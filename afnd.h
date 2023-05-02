#ifndef AFND_H
#define AFND_H
#include <stdbool.h>
#define MAX_STATES 10
#define ALPHABET_SIZE 5
typedef bool booleanArray[MAX_STATES];

typedef struct{
	int states[MAX_STATES];
	int alphabet[ALPHABET_SIZE];
	booleanArray delta[MAX_STATES][ALPHABET_SIZE];
	int initialState;
	int finalStates[MAX_STATES];
}AFN;

AFN readAutomaton(char *fileName);
void automatonToString(AFN automaton);
AFN initAutomaton(AFN automaton);
void writeAutomaton(char *fileName, AFN automaton);

#endif
