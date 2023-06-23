#include <stdio.h>
// #include "../utils/productions.h"
#include <string.h>
#include <stdbool.h>
#include "parsersLL1.h"

char chain[100];
int i;


int main(){
    printf("entro el paeseo\n");
    printf("result True == %s \n", parser("(a)#") ? "True" : "False");
    printf("result False == %s \n", parser("(a)") ? "True" : "False" );
    printf("result False == %s \n", parser(")a(#") ? "True" : "False" );
}

bool parser(char c[]){
    i = 0;
    strcpy(chain, c);
    printf("empezo parseo\n");
    return S();

}

// Grammar rule: S -> E#
bool S() {
    printf("Parseando S() cc = %c\n", chain[i]);
    if(chain[i] == '(' || chain[i] == 'a' || chain[i] == 'b' || chain[i] == 'c'){
        if (E()) { // Call non-terminal T
            if (chain[i] == '#'){ // Call non-terminal E'
                i++;
                return true;
            }
        }
    }
    return false;
}

// Grammar rule: E -> TG G = E'
bool E() {
    printf("Parseando E() cc = %c\n", chain[i]);
    if(chain[i] == '(' || chain[i] == 'a' || chain[i] == 'b' || chain[i] == 'c'){
        if (T()) {
            if (G())
                return true;
        }
    }
    return false;
}

// Grammar rule: G -> |TG G = E'
bool G() {
    printf("Parseando G() cc = %c\n", chain[i]);
    if(chain[i] == '|'){
        i++;
        if (T()){
            if (G())
                return true;
        }
        return false;
    }else{
        return true;
    }
}

// Grammar rule: T -> FN N = T'
bool T() {
    printf("Parseando T() cc = %c\n", chain[i]);
    if(chain[i] == '(' || chain[i] == 'a' || chain[i] == 'b' || chain[i] == 'c'){
        if (F()) { // Call non-terminal T
            if (N()) // Call non-terminal E'
                return true;
        }
    }
    return false;
}

// Grammar rule: N -> .FN N = T'
bool N() {
    printf("Parseando N() cc = %c\n", chain[i]);
    if(chain[i] == '.'){
        i++;
        if (F()){ // Call non-terminal T
            if(N()) // Call non-terminal E'
                return true;
        }
        return false; 
    }else{
        return true;
    }
}

// Grammar rule: F -> PU U = F'
bool F() {
    printf("Parseando F() cc = %c\n", chain[i]);
    if(chain[i] == '(' || chain[i] == 'a' || chain[i] == 'b' || chain[i] == 'c'){
        if (P()) { // Call non-terminal T
            if (U()) // Call non-terminal E'
                return true;
        }
    }
    return false;
}

// Grammar rule: U -> * U = F'
bool U() {
    printf("Parseando U() cc = %c\n", chain[i]);
    if(chain[i] == '*'){
        i++;
        return true;
    }else{
        return true;
    }
    return false;
}

// Grammar rule: P -> (E) P -> L
bool P() {
    printf("Parseando P() cc = %c\n", chain[i]);
    if(chain[i] == '('){
        i++;
        if (E()) { // Call non-terminal T
            if (chain[i] == ')'){ // Call non-terminal E'
                i++;
                return true;
            }
        }
        return false;
    }else{
        if(L())
            return true; 
    }
    return false;
}

// Grammar rule: L -> a
// Grammar rule: L -> b
// Grammar rule: L -> c
bool L() {
    printf("Parseando L() cc = %c\n", chain[i]);
    if(chain[i] == 'a'){
        i++;
        return true;
    }else if(chain[i] == 'b'){
        i++;
        return true;
    }else if(chain[i] == 'c'){
        i++;
        return true;
    }
    return false;
}












// bool parserNoTerminal(GramaticLL1Production *gramaticProductions, char currentSymbol, char alpha){
//     return false;
// }
    
//     GramaticLL1Production *alphaProductions = malloc(sizeof(GramaticLL1Production));
//     Production *production = malloc(sizeof(Production));
    
//     getAlphaProductions(gramaticProductions ,alpha, alphaProductions);
//     findProduction(*alphaProductions, chain[i], production);
//     if(!isEmptyProduction(*production)){//si es una produchain[i]ion retorna falso, significa q no hay produchain[i]ion q en sus simbolos directrices tenga el simbolo corriente
//         Alphabet alphabet = getProductionBeta(*production);
//         for(int i = 0; i < alphabet.cant; i++){
//             char alphabetSymbol = alphabet.alphabet[i];
//             printf("caracter de la cadena %c - simbolo procesado %c\n", chain[i], alphabetSymbol);
//             if(!procesar(alphabetSymbol, currentSymbol, gramaticProductions)){
//                 free(production);
//                 free(alphaProductions);
//                 return false;
//             }
//         }
//     }else{
//         return false;
//     }
//     free(production);
//     free(alphaProductions);
//     return true;
// }

// bool procesar(char alpha, char currentSymbol, GramaticLL1Production *gramaticProductions){
//     if(isNoTerminalSymbol(alpha)){
//         return parserNoTerminal(gramaticProductions, currentSymbol, alpha);
//     }else{
//         return eat(alpha, currentSymbol);
//     }
// }

// bool eat(char alpha, char currentSymbol){
//     if(alpha == chain[i]){
//         return i++;
//     }
//     return false;
// }