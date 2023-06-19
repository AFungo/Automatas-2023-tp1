#include <stdio.h>

#include "parsersLL1.h"
#include "../utils/productions.h"

bool parserDecendenteRecursivo(GramaticLL1Production *gramaticProductions, char alpha, char currentSymbol){

    Production *sdProduction = findProduction(gramaticProductions, currentSymbol);

    if(!isEmptyProduction(*sdProduction)){
        Alphabet alphabet = getProductionBeta(*sdProduction);
        for(int i = 0; i < alphabet.cant; i++){
            char alphabetSymbol = alphabet.alphabet[i];
            return procesar(alphabetSymbol, currentSymbol, gramaticProductions);
        }
    }else{
        return false;
    }
}

bool procesar(char alpha, char currentSymbol, GramaticLL1Production *gramaticProductions){
    if(isNoTerminalSymbol(alpha)){
        return parserDecendenteRecursivo(gramaticProductions, alpha, currentSymbol);
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
