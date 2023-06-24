#ifndef PARSERLL1_h
#define PARSERLL1_h

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "noDeterministicAutomaton.h"
#include "../utils/alphabetUtils.h"
#include "../utils/productions.h"
#include "../models/automatonAlgorithms.h"

typedef struct{

    GramaticLL1Production productions;
    Alphabet alphabet;

}GramaticLL1;
bool minigrep(char chain[], char regExpre[]);
AFN *getAFNFromRegExp(char c[], AFN **afn);
bool parser(char c[], AFN **afn);
bool S(AFN **afn);
bool E(AFN **afn);
bool G(AFN **afn);
bool T(AFN **afn);
bool N(AFN **afn);
bool F(AFN **afn);
bool U(AFN **afn);
bool P(AFN **afn);
bool L(AFN **afn);

#endif