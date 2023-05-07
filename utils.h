#ifndef UTILS_h
#define UTILS_h
#include "afnd.h"

void addInitialStateToAutomaton(AFN *automaton, int symbol);
void automatonToString(AFN automaton);
void getMultipleTransitions(AFN *automaton, char *trans, Alphabet *transitions);
void addSymbolToAutomaton(AFN *automaton, int symbol);
bool pertenceAlph(int alph[], char *chain);
void initAutomaton(AFN *automaton);
void addStateToAutomaton(AFN *automaton, int state);
void addNewSymbolToAlphabet(Alphabet *alphabet, int symbol);
void addNewDeltaToAutomaton(AFN *automaton, int departure, int arrival, int symbol);
void addNewFinalStateToAutomaton(AFN *automaton, int state);
void initAlphabet(Alphabet *alphabet);
int getStateIndex(States states, int state);
int getAlphabetIndex(Alphabet alphabet, int symbol);
bool isFinalState(AFN automaton, int s);
#endif