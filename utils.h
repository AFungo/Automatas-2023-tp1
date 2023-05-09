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
struct Pair objectIsInMatriz(int m[matrixSize][MAX_STATES], int a[MAX_STATES]);
bool isInMatrix(int m[matrixSize][MAX_STATES], int a[MAX_STATES]);
int posInMatrix(int m[matrixSize][MAX_STATES], int a[MAX_STATES]);
void addFinal(AFN *afn, AFD *afd, int matrix[matrixSize][MAX_STATES],int cantOfElem);
void addState(int states[MAX_STATES], int matrix[matrixSize][MAX_STATES], int *cantOfElem);
int* closure(int states[MAX_STATES], booleanArray delta[MAX_STATES][ALPHABET_SIZE]);
int* move(int states[MAX_STATES], int alph, booleanArray delta[MAX_STATES][ALPHABET_SIZE]);
int* initialClosure(int s, int alph, booleanArray delta[MAX_STATES][ALPHABET_SIZE]);
void addStateToStates(States *states, int state);
#endif