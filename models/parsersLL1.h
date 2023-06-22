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

bool parser(GramaticLL1 gramatic, char chain[]);
/*
*   esta funcion va a tomar a grsamatica ll1 y va ir verificando la cadena desde el simbolo corriente pag 104 del apunte
*/
bool parserNoTerminal(GramaticLL1Production *gramaticProductions, char currentSymbol, char alpha);
/*
* esta funcion va a decdir si el  simbolo es terminal o no terminal para luego ver como lo procesa pag 104 del apunte 
*/
bool procesar(char alphabetSymbol, char currentSymbol, GramaticLL1Production *gramaticProductions);
/*
* decide si pertenece o no a la cadena pag 104 del apunte
*/
bool eat(char alpha, char currentSymbol);


#endif