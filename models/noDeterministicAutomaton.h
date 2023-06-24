#ifndef AFND_H
#define AFND_H
#include <stdbool.h>
#include <math.h>
#include "../utils/stateUtils.h"
#include "../utils/alphabetUtils.h"

typedef bool booleanArray[MAX_STATES];

typedef struct{
	States states;
	Alphabet alphabet;
	booleanArray delta[MAX_STATES][ALPHABET_SIZE];
	int initialState;
	States finalStates;
	int alphabet_size;
}AFN;

void addInitialStateToAutomaton(AFN *automaton, int symbol);
void automatonToString(AFN automaton);
void getMultipleTransitions(AFN *automaton, char *trans, Alphabet *transitions);
void addSymbolToAutomaton(AFN *automaton, int symbol);
void initAutomaton(AFN *automaton);
void addStateToAutomaton(AFN *automaton, int state);
void addNewDeltaToAutomaton(AFN *automaton, int departure, int arrival, int symbol);
void addNewFinalStateToAutomaton(AFN *automaton, int state);
bool isFinalState(AFN automaton, int s);
void appendSymbolsToAFN(AFN *automaton, AFN b);
void appendStatesToAFN(AFN *automaton, AFN b, int statesIndex[MAX_STATES], int *stateNumber);
void appendDeltaToAFN(AFN *automaton, AFN b, int statesIndex[MAX_STATES]);
void appendFinalStatesToAFN(AFN *automaton, AFN b, int statesIndex[MAX_STATES]);
States getAFNFinalStates(AFN automaton);
AFN *createAutomaton(int symbol);
#endif