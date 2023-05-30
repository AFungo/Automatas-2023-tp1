#ifndef UTILS_h
#define UTILS_h
#include "../models/noDeterministicAutomaton.h"
#include "../models/deterministicAutomaton.h"
#include "partitions.h"
#define matrixSize (1 << MAX_STATES) -1

struct Pair {
    bool first;
    int second;
};

// struct Pair objectIsInMatriz(States m[matrixSize], States a);
bool isInMatrix(States m[matrixSize], States a, int matrizSize);
int posInMatrix(States m[matrixSize], States a);
void addFinalStateToMatrix(AFN *afn, AFD *afd, int matrix[matrixSize][MAX_STATES],int cantOfElem);
void addState(States states, States matrix[matrixSize], int *cantOfElem);
States *closure(States states, AFN afn);
States *move(States states, int alph, AFN afn);
States *initialClosure(int s, AFN afn);
bool haveFinalState(AFN *afn, States state);
bool equivalenceClassAreEquals(AFD afd, int markedState, int unMarkedState, Partitions partitions);
void pintMAtrix(States matrix[matrixSize], int cant);



#endif