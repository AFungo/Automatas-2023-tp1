#ifndef PARSERLL1_h
#define PARSERLL1_h

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "noDeterministicAutomaton.h"
#include "../utils/alphabetUtils.h"
#include "../utils/productions.h"


typedef struct{

    GramaticLL1Production productions;
    Alphabet alphabet;

}GramaticLL1;
AFN *gramatictoAFN();
bool parser(char c[]);
bool S();
bool E();
bool G();
bool T();
bool N();
bool F();
bool U();
bool P();
bool L();

#endif