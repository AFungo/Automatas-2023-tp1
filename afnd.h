#ifndef AFND_H
#define AFND_H
#include <stdbool.h>
#define MAX_STATES 3
#define ALPHABET_SIZE 3
#define matrixSize (1 << MAX_STATES) -1
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

typedef struct{
	int states[matrixSize];
	int alphabet[ALPHABET_SIZE];
	int delta[MAX_STATES][ALPHABET_SIZE]; // int o bool?
	int initialState[MAX_STATES];
	int finalState[MAX_STATES];
}AFD;

struct Pair {
    bool first;
    int second;
}Pair;


AFN readAutomaton(char *fileName);
void writeAutomaton(char *fileName, AFN automaton);
bool pertence(AFN *t, char *chain);
AFD aFNtoAFD(AFN *a);

#endif
