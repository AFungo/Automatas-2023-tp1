#ifndef UTILS_h
#define UTILS_h
#include "afnd.h"

struct Pair {
    bool first;
    int second;
};

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
// struct Pair objectIsInMatriz(States m[matrixSize], States a);
bool isInMatrix(States m[matrixSize], States a, int matrizSize);
bool statesAreEquals(States a,States b);
int posInMatrix(States m[matrixSize], States a);
void addFinal(AFN *afn, AFD *afd, int matrix[matrixSize][MAX_STATES],int cantOfElem);
void addState(States states, States matrix[matrixSize], int *cantOfElem);
States *closure(States states, AFN afn);
States *move(States states, int alph, AFN afn);
States *initialClosure(int s, AFN afn);
void addStateToStates(States *states, int state);
bool haveFinalState(AFN *afn, States state);
void initADF(AFD *afd);
void printStates(States s);
void pintMAtrix(States matrix[matrixSize], int cant);
void cancatenateStates(States *state, States newState);
#endif