start: main
	./main

build: input.c menu.c tree_utils.c comparators.c main.c
	gcc input.c menu.c tree_utils.c comparators.c main.c -o main
