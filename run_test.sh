gcc -o test1 testStringBelongTheLanguage.c afnd.c utils.c
gcc -o test2 testReadBasicAutomaton.c afnd.c utils.c
gcc -o test3 testWriteBasicAutomaton.c afnd.c utils.c
gcc -o test4 testReadAutomatonWLambda.c afnd.c utils.c
gcc -o test5 testWriteAutomatonWLambda.c afnd.c utils.c
gcc -o test6 testTransformAFNtoAFD.c afnd.c utils.c

./test1
./test2
./test3
./test4
./test5
./test6
