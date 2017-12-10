all: main.c control.c
	gcc -o "main" main.c
	gcc -o "control" control.c
