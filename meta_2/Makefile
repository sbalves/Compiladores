FILENAME = gocompiler.l

exe: ${FILENAME}
	lex ${FILENAME}
	clang -o gocompiler lex.yy.c

clear:
	rm -rf *gocompiler
