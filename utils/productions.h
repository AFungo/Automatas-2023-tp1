#ifndef PRODUCTIONS_h
#define PRODUCTIONS_h

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_PRODUCTIONS 100

#include "../utils/alphabetUtils.h"

typedef struct{

    char alpha;
    Alphabet beta;
    Alphabet SD;

}Production;

typedef struct{

    Production production[MAX_PRODUCTIONS];
    int cant;

}GramaticLL1Production;

Production *getAlphaProductions(GramaticLL1Production *gramaticProductions, char alpha);
Production *findProduction(GramaticLL1Production *productions, char currentSymbol);
bool isEmptyProduction(Production sdProduction);
Production *emptyProduction();
Alphabet getProductionBeta(Production sdProduction);
bool isNoTerminalSymbol(char alpha);


#endif