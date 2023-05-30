#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stateUtils.h"

bool contains(States states, int state){
	for(int i = 0; i < states.cant; i++){
		if(states.states[i] == state){
			return true;
		}
	}
	return false;	
}

void addStateToStates(States *states, int state){
	if(!contains(*states, state)){
		states->states[states->cant] = state;
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

void removeStates(States *state, States remove){
	States *newState = malloc(sizeof(States));
	for(int i = 0; i < state->cant; i++){
		if(!contains(remove, state->states[i])){
			addStateToStates(newState, state->states[i]);
		}
	}
	*state = *newState;
}

void printStates(States s){
	printf("[");
	for(int j = 0;j<s.cant; j++){
		printf("%d,", s.states[j]);
	}
	printf("]\n");
}