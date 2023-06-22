#include <stdio.h>

#include "parsersLL1.h"
#include "../utils/productions.h"


bool parser(GramaticLL1 gramatic, char chain[]){
    int i = 0;
    while(chain[i]!='\0'){
        Production *production = malloc(sizeof(Production));
        // findProduction(gramatic.productions, chain[i], production);
        char noTerminal = production->alpha;
        if(!parserNoTerminal(&gramatic.productions, chain[i], 'S')){
            return false;
        }
    }
    return true;
}

bool parserNoTerminal(GramaticLL1Production *gramaticProductions, char currentSymbol, char alpha){
    
    GramaticLL1Production *alphaProductions = malloc(sizeof(GramaticLL1Production));
    Production *production = malloc(sizeof(Production));
    
    getAlphaProductions(gramaticProductions ,alpha, alphaProductions);
    findProduction(*alphaProductions, currentSymbol, production);   
    // printf("production \n");
    // printProduction(*production);
    // printf("------------------------------");
    if(!isEmptyProduction(*production)){//si es una produccion retorna falso, significa q no hay produccion q en sus simbolos directrices tenga el simbolo corriente
        Alphabet alphabet = getProductionBeta(*production);
        for(int i = 0; i < alphabet.cant; i++){
            char alphabetSymbol = alphabet.alphabet[i];
            if(procesar(alphabetSymbol, currentSymbol, gramaticProductions)){
                // printf("\n\nFue TRUE\n\n");
                return true;
            }
        }
    }
    return false;
}

bool procesar(char alpha, char currentSymbol, GramaticLL1Production *gramaticProductions){
    if(isNoTerminalSymbol(alpha)){
        return parserNoTerminal(gramaticProductions, currentSymbol, alpha);
    }else{
        return eat(alpha, currentSymbol);
    }
}

bool eat(char alpha, char currentSymbol){
    if(alpha == currentSymbol){
        return true;
    }

    return false;
}