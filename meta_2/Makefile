FILENAME = gocompiler.l
FILENAME2 = gocompiler.y
EXE = gocompiler

exe: ${FILENAME} ${FILENAME2}
	lex ${FILENAME}
	yacc -y -d -v -d ${FILENAME2}
	cc -o ${EXE} y.tab.c lex.yy.c

clear:
	rm -rf *${EXE}