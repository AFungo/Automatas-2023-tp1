#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stateUtils.h"

void addStateToStates(States *states, int state){
	bool isNewState = true;
	int i = 0;
	for(i = 0; i < states->cant; i++){
		if(states->states[i] == state){
			isNewState = false;
		}
	}
	if(isNewState){
		states->states[i] = state;
		states->cant++;
	}
}

int getStateIndex(States states, int state){
	for(int i = 0; i < states.cant; i++){
		if(states.states[i] == state) return i;
	}
	return -1;
}

bool statesAreEquals(States a,States b){
	if(a.cant != b.cant) return false;
	for(int i=0; i<a.cant; i++){
		bool isIn = false;
		for(int j=0; j<b.cant; j++){
			if(a.states[i] == b.states[j]){
				isIn = true;
				j = b.cant+1;
			}
		}
		if(!isIn){
			return false;
		}
	}
	return true;
}

void cancatenateStates(States *state, States newState){
	for(int i = 0; i <newState.cant; i++){
		addStateToStates(state, newState.states[i]);
	}
}

void printStates(States s){
	printf("[");
	for(int j = 0;j<s.cant; j++){
		printf("%d,", s.states[j]);
	}
	printf("]\n");
}