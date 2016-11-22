all: convgerber

convgerber: convgerber.c
	gcc -Wall convgerber.c -o convgerber

install: convgerber
	cp convgerber /usr/local/bin

clean:
	rm convgerber 
