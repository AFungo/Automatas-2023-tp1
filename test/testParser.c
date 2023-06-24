#include "../models/parsersLL1.h"
#include <stdio.h>

int main(){
    AFN *afn;
    printf("********************************\nTest parser\n\n");
    printf("result for: (a)# True == %s \n", parser("(a)#", &afn) ? "True" : "False");
    printf("------------------------------\n\n");
    printf("result for: ((a*).b)|c*# True == %s \n", parser("((a*).b)|c*#", &afn) ? "True" : "False");
    printf("------------------------------\n\n");
    printf("result for: (b*)# True == %s \n", parser("(b*)#", &afn) ? "True" : "False");
    printf("------------------------------\n\n");
    printf("result for: (a) False == %s \n", parser("(a)", &afn) ? "True" : "False" );
    printf("------------------------------\n\n");
    printf("result for: )a(# False == %s \n", parser(")a(#", &afn) ? "True" : "False" );
}