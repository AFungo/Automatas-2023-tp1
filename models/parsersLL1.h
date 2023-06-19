#ifndef PARSERLL1_h
#define PARSERLL1_h

#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#include "../utils/alphabetUtils.h"
#include "../utils/productions.h"


typedef struct{

    GramaticLL1Production productions;
    Alphabet alphabet;

}GramaticLL1;


bool parserDecendenteRecursivo(GramaticLL1Production *gramaticProductions, char alpha, char currentSymbol);
bool procesar(char alphabetSymbol, char currentSymbol, GramaticLL1Production *gramaticProductions);
bool eat(char alpha, char currentSymbol);

#endif