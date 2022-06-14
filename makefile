all:
	gcc main.c -o main
	gcc test.c -o test

clean:
	rm -rf main
	rm -rf a.out