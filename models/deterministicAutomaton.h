#ifndef DETERMINISTICAUTOMATON_h
#define DETERMINISTICAUTOMATON_h

#include "../utils/stateUtils.h"
#include "../utils/alphabetUtils.h"

typedef struct{
	States states;
	Alphabet alphabet;
	int delta[MAX_STATES][ALPHABET_SIZE];
	int initialState;
	States finalStates;
}AFD;

void initAFD(AFD *afd);
void addNewDeltaToAFD(int departure, int arrival, int symbol, AFD *afd);
void addNewFinalStateToAFD(AFD *afd, int state);
void addStateToAFD(AFD *afd, int state);
void addInitialStateToAFD(AFD *afd, int satate);

#endif