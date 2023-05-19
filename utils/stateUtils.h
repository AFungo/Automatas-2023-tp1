#ifndef STATEUTILS_h
#define STATEUTILS_h

#include <stdbool.h>

#define MAX_STATES 10

typedef struct{
	int states[MAX_STATES];
	int cant;
}States;

int getStateIndex(States states, int state);
bool statesAreEquals(States a,States b);
void addStateToStates(States *states, int state);
void printStates(States s);
void cancatenateStates(States *state, States newState);

#endif