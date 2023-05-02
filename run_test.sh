gcc -o test1 testCreateAutomaton.c afnd.c
gcc -o test2 testReadBasicAutomaton.c afnd.c
gcc -o test3 testWriteBasicAutomaton.c afnd.c

./test1
./test2
./test3
