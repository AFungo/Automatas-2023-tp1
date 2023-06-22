#ifndef PRODUCTIONS_h
#define PRODUCTIONS_h

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

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


GramaticLL1Production *getAlphaProductions(GramaticLL1Production *gramaticProductions, char alpha, GramaticLL1Production *alphaProductions);
void findProduction(GramaticLL1Production productions, char currentSymbol, Production *production);
bool isEmptyProduction(Production sdProduction);
Production emptyProduction();
Alphabet getProductionBeta(Production sdProduction);
bool isNoTerminalSymbol(char alpha);
void addProduction(GramaticLL1Production *gramaticProductions, Production production);
void initGramaticProductions(GramaticLL1Production *gramaticProductions);
bool belongsToProductionbSD(Production production, char symbol);
void addSymbolToBetaProduction(Production *production, char symbol);
void addSymbolToSDProduction(Production *production, char symbol);
void addSymbolToAlphaProduction(Production *production, char symbol);
void printProduction(Production production);
void printLL1Productios(GramaticLL1Production productions);
void addStringToBeta(Production *production, char b[]);

#endif