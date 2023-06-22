#include "productions.h"

GramaticLL1Production *getAlphaProductions(GramaticLL1Production *gramaticProductions, char alpha, GramaticLL1Production *alphaProductions){
    initGramaticProductions(alphaProductions);
    for(int i = 0; i < gramaticProductions->cant; i++){
        Production production = gramaticProductions->production[i];
        char productionAlpha = production.alpha;
        if(productionAlpha == alpha){
            // printf("produccion add \n\n");
            // printProduction(production);
            addProduction(alphaProductions, production);
            // printf("...............................\n\n");
        }
    }
}

bool belongsToProductionbSD(Production production, char symbol){
    return symbolBelongsToAlphabet(production.SD, parseCharToInt(symbol));
}

void findProduction(GramaticLL1Production productions, char currentSymbol, Production *production){
    *production = emptyProduction();
    // printf("tengo tantas produccion %d\n", productions.cant);
    for(int i=0; i<productions.cant; i++){
        // printf("current symbol %c \n", currentSymbol);
        if(belongsToProductionbSD(productions.production[i], currentSymbol)){
            // printf("%d ENTEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE \n\n\n", i);
            // printProduction(productions.production[i]);
            *production = productions.production[i];
        }
    }
}

Production emptyProduction(){
    Production *production = malloc(sizeof(Production));

    production->alpha = '&'; //empty symbol
    initAlphabet(&production->beta);
    initAlphabet(&production->SD);
    
    return *production;
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
    return islower(alpha);
}

void addProduction(GramaticLL1Production *gramaticProductions, Production production){
    gramaticProductions->production[gramaticProductions->cant] = production;
    gramaticProductions->cant++;
}

void initGramaticProductions(GramaticLL1Production *gramaticProductions){
    for(int i=0; i<MAX_PRODUCTIONS; i++){
        gramaticProductions->production[i] = emptyProduction();
    }
    gramaticProductions->cant = 0;
}

void addSymbolToBetaProduction(Production *production, char symbol){
    addNewSymbolToAlphabet(&production->beta, parseIntToChar(symbol));
}

void addSymbolToAlphaProduction(Production *production, char symbol){
    production->alpha = symbol; 
}

void addSymbolToSDProduction(Production *production, char symbol){
    addNewSymbolToAlphabet(&production->SD, symbol);
}

void printProduction(Production production){
    printf("%c -> ", production.alpha);
    
    for(int i=0; i<production.beta.cant; i++){
        printf("%c", parseIntToChar(production.beta.alphabet[i]));
    }
    printf(" - SD = ");
    for(int i=0; i<production.SD.cant; i++){
        printf("%c ", parseIntToChar(production.SD.alphabet[i]));
    }
    printf("\n");
}

void printLL1Productios(GramaticLL1Production productions){
    for(int i=0; i< productions.cant; i++){
        printProduction(productions.production[i]);
    }
}

void addStringToBeta(Production *production, char b[]){
     int i = 0;
     while (b[i] != '\0') {
        addSymbolToBetaProduction(production, b[i]);
        i++;
    }
}
