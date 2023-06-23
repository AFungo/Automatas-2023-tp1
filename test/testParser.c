#include "../models/parsersLL1.h"
#include <stdio.h>

int main(){

    printf("------------------------------\n\n");
    printf("result True == %s \n", parser("(a)#") ? "True" : "False");
    printf("------------------------------\n\n");
    printf("result False == %s \n", parser("(a)") ? "True" : "False" );
    printf("------------------------------\n\n");
    printf("result False == %s \n", parser(")a(#") ? "True" : "False" );
}