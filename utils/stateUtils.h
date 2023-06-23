#ifndef STATEUTILS_h
#define STATEUTILS_h

#include <stdbool.h>

#define MAX_STATES 20

typedef struct{
	int states[MAX_STATES];
	int cant;
}States;

bool contains(States states, int state);
int getStateIndex(States states, int state);
bool statesAreEquals(States a,States b);
void addStateToStates(States *states, int state);
void printStates(States s);
void cancatenateStates(States *state, States newState);
void removeStates(States *state, States remove);

#endif