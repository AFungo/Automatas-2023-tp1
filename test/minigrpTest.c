#include "../models/noDeterministicAutomaton.h"
#include "../utils/utils.h"
#include <stdio.h>
#include "../models/parsersLL1.h"
#include "../models/automatonAlgorithms.h"

void test(char chain[], char regExp[]){
    minigrep(chain, regExp);
}

int main(){//IMPORTANTE los test no se puede conrrer de mas de a 2, si no retorna segmentation fault, individualmente andan a la perfeccion
    printf("\n**********************************************\nTEST Gramatic TO AFND\n\n");
    test("aab","((a*).b)|c*#");
    printf("\n-----------------------------------------------------\n");
    test("ccc","((a*).b)|c*#");
    printf("\n-----------------------------------------------------\n");
    test("aaa","a*#");
    printf("\n-----------------------------------------------------\n");
    test("aabb","(a*).b*#");
    // printf("\n**********************************************\n\n");
}
