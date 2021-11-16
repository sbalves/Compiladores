FILENAME = gocompiler.l
FILENAME2 = gocompiler.y
EXE = gocompiler

exe: ${FILENAME}
	lex -l ${FILENAME}
	yacc -d -v ${FILENAME2}
	clang -o gocompiler lex.yy.c < syntax_errors_stmt.dgo > syntax_errors_stmt_t.out
	cc -Wall -o ${EXE} y.tab.c lex.yy.c

clear:
	rm -rf *${EXE}