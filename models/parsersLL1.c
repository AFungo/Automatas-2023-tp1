#include <stdio.h>
// #include "../utils/productions.h"
#include <string.h>
#include <stdbool.h>


#include "parsersLL1.h"

char chain[100];
int i;


AFN *getAFNFromRegExp(char c[], AFN **afn){
    parser(c, afn);
    return *afn;
}

bool parser(char c[], AFN **afn){
    i = 0;
    strcpy(chain, c);
    return S(afn);

}

// Grammar rule: S -> E#
bool S(AFN **afn) {
    printf("Parseando S() cc = %c\n", chain[i]);
    if(chain[i] == '(' || chain[i] == 'a' || chain[i] == 'b' || chain[i] == 'c'){
        if (E(afn)) {
            if (chain[i] == '#'){
                return true;
            }
        }
    }
    return false;
}

// Grammar rule: E -> TG G = E'
bool E(AFN **afn) {
    printf("Parseando E() cc = %c\n", chain[i]);
    if(chain[i] == '(' || chain[i] == 'a' || chain[i] == 'b' || chain[i] == 'c'){
        if (T(afn)) {
            if (G(afn))            
                return true;
        }
    }
    return false;
}

// Grammar rule: G -> |TG G = E'
bool G(AFN **afn) {
    printf("Parseando G() cc = %c\n", chain[i]);
    if(chain[i] == '|'){
        AFN *a;
        i++;
        if (T(&a)){
            if (G(&a)){
                *afn = automatonUnion(**afn, *a);
                free(a);
                return true;
            }
        }
        return false;
    }else{
        return true;
    }
}

// Grammar rule: T -> FN N = T'
bool T(AFN **afn) {
    printf("Parseando T() cc = %c\n", chain[i]);
    if(chain[i] == '(' || chain[i] == 'a' || chain[i] == 'b' || chain[i] == 'c'){
        if (F(afn)) { // Call non-terminal T
            if (N(afn)) // Call non-terminal E'
                return true;
        }
    }
    return false;
}

// Grammar rule: N -> .FN N = T'
bool N(AFN **afn) {
    printf("Parseando N() cc = %c\n", chain[i]);
    if(chain[i] == '.'){
        AFN *a;
        i++;
        if (F(&a)){ // Call non-terminal T
            if(N(&a)){ // Call non-terminal E'
                *afn = automatonConcatenacion(**afn, *a);
                free(a);
                return true;
            }
        }
        return false; 
    }else{
        return true;
    }
}

// Grammar rule: F -> PU U = F'
bool F(AFN **afn) {
    printf("Parseando F() cc = %c\n", chain[i]);
    if(chain[i] == '(' || chain[i] == 'a' || chain[i] == 'b' || chain[i] == 'c'){
        if (P(afn)) { // Call non-terminal T
            if (U(afn)) // Call non-terminal E'
                return true;
        }
    }
    return false;
}

// Grammar rule: U -> * U = F'
bool U(AFN **afn) {
    if(chain[i] == '*'){
        *afn = automatonKlenneClausure(**afn);
        i++;
        return true;
    }else{
        return true;
    }
    return false;
}

// Grammar rule: P -> (E) P -> L
bool P(AFN **afn) {
    printf("Parseando P() cc = %c\n", chain[i]);
    if(chain[i] == '('){
        i++;
        if (E(afn)) {
            if (chain[i] == ')'){
                i++;
                return true;
            }
        }
        return false;
    }else{
        if(L(afn))
            return true; 
    }
    return false;
}

// Grammar rule: L -> a
// Grammar rule: L -> b
// Grammar rule: L -> c
bool L(AFN **afn) {
    printf("Parseando L() cc = %c\n", chain[i]);
    if(chain[i] == 'a'){
        *afn = createAutomaton((int) 'a');
        i++;
        return true;
    }else if(chain[i] == 'b'){
        *afn = createAutomaton((int)'b');
        i++;
        return true;
    }else if(chain[i] == 'c'){
        *afn = createAutomaton((int) 'c');
        i++;
        return true;
    }
    return false;
}

bool minigrep(char chain[], char regExpre[]){
    AFN *afn = malloc(sizeof(AFN));
    getAFNFromRegExp(regExpre, &afn);
    automatonToString(*afn);
    AFD afd = aFNtoAFD(afn);
    printf("no me la banque\n");
    *afn = AFDtoAFN(afd);

    int length = strlen(chain);

    for (int start = 0; start < length; start++) {
        for (int len = 1; len <= length - start; len++) {
            for (int i = start; i < start + len; i++) {
                char* subchain = malloc((len + 1) * sizeof(char));
                strncpy(subchain, chain + start, len);
                subchain[len] = '\0';
                printf("%s pertence %s\n", subchain, pertence(afn, chain) ? "True":"False");
                free(subchain);
            }
        }
    }
}









