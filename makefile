default:
	gcc Wordle.c -c
	gcc -Wall Wordle.o -o a.out
run:
	./a.out Wordle.c
clear:
	rm *.o
	rm *.out
