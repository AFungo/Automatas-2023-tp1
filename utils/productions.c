#include "productions.h"

Production *getAlphaProductions(GramaticLL1Production *gramaticProductions, char alpha){

    for(int i = 0; i < gramaticProductions->cant; i++){
        char productionAlpha = gramaticProductions->production[i].alpha;
        if(productionAlpha == alpha){
            return &gramaticProductions->production[i];
        }
    }
    return emptyProduction();
}



Production *findProduction(GramaticLL1Production *productions, char currentSymbol){

    for(int i=0; i<productions->cant; i++){
        if(pertenceAlph(productions->production[i].SD.alphabet, (int)currentSymbol)){
            return &productions->production[i];
        }
    }
    return emptyProduction();
}

Production *emptyProduction(){
    Production *production = malloc(sizeof(Production));

    production->alpha = '&'; //empty symbol
    initAlphabet(&production->beta);
    initAlphabet(&production->SD);
    
    return production;
}

bool isEmptyProduction(Production sdProduction){
    return  sdProduction.alpha == '&' && 
            sdProduction.beta.cant == 0 && 
            sdProduction.SD.cant == 0;
}


Alphabet getProductionBeta(Production sdProduction){
    return sdProduction.beta;
}

bool isNoTerminalSymbol(char alpha){
    //chequear si el simbolo es lowercase
    return false;
}
