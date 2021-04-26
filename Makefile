# Makefile

sha512: sha512.c
	cc -o sha512 sha512.c

clean:
	rm -f sha512