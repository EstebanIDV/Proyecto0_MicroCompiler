compile:
	gcc -Wall scanner.c translator.c parser.c symbols_table.c main.c types.h -o micro

clean:
	rm -rf micro
