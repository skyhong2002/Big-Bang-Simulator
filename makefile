all:
	gcc main.c code/*.c -o main -lm

clean:
	rm -rf main
	rm -rf *.txt