gcc -o test1 test/minigrpTest.c utils/*.c models/*.c
gcc -o test2 test/gramaticToAFNTest.c utils/*.c models/*.c
gcc -o test3 test/testParser.c utils/*.c models/*.c

./test1
./test2
./test3

ls | grep -e "test[0-9]" | xargs rm
