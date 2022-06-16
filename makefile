all:
	gcc main.c code/*.c -o main

clean:
	rm -rf main
	rm -rf a.out