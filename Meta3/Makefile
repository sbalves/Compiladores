FILENAME1 = gocompiler.l
FILENAME2 = gocompiler.y
FILENAME3 = ast.c
FILENAME4 = ast.h
FILENAME5 = structures.h
FILENAME6 = semantic_analysis.c
FILENAME7 = semantic_analysis.h
FILENAME8 = auxiliar_functions.c
FILENAME9 = auxiliar_functions.h
FILENAME10 = symbol_table.c
FILENAME11 = symbol_table.h

EXE = gocompiler
ZIP := zip

ifneq (,$(findstring xterm,${TERM}))
	RED     := $(shell tput -Txterm setaf 1)
	GREEN   := $(shell tput -Txterm setaf 2)
	BLUE    := $(shell tput -Txterm setaf 6)
	YELLOW  := $(shell tput -Txterm setaf 3)
	RESET   := $(shell tput -Txterm sgr0)
	BOLD    := $(shell tput bold)
	NORM    := $(shell tput sgr0)
else
	RED     := ""
	GREEN   := ""
	BLUE    := ""
	RESET   := ""
	BOLD 	:= ""
	NORM 	:= ""
endif

exe: ${FILENAME1} ${FILENAME2}
		@echo "$(GREEN)$(BOLD)--------------------$(NORM)$(RESET)$(GREEN)COMPILING$(NORM)$(RESET)$(GREEN)$(BOLD)---------------------$(NORM)$(RESET)$(BLUE)"
		lex ${FILENAME1}
		yacc -y -d -v -t ${FILENAME2}
		cc -o ${EXE} -ggdb3 y.tab.c lex.yy.c ast.c semantic_analysis.c auxiliar_functions.c symbol_table.c
		#valgrind --leak-check=full --show-leak-kinds=all --log-file="valgrind.txt" ./gocompiler < meta3_testes/logical_operators.dgo
		@echo "$(GREEN)$(BOLD)-----------------------$(NORM)$(RESET)$(GREEN)Done$(NORM)$(RESET)$(GREEN)$(BOLD)-----------------------$(NORM)$(RESET)"

clear:
	rm -rf *${EXE}
	rm -rf $(EXE).zip

zip:
	@echo "$(GREEN)$(BOLD)--------------$(NORM)$(RESET)$(GREEN)Compressing $(EXE)$(NORM)$(RESET)$(GREEN)$(BOLD)-------------$(NORM)$(RESET)$(BLUE)"
	zip -r $(EXE).zip ${FILENAME1} ${FILENAME2} ${FILENAME3} ${FILENAME4} ${FILENAME5} ${FILENAME6} ${FILENAME7} ${FILENAME8} ${FILENAME9} ${FILENAME10} ${FILENAME11}
	@echo "$(GREEN)$(BOLD)-----------------------$(NORM)$(RESET)$(GREEN)Done$(NORM)$(RESET)$(GREEN)$(BOLD)----------------------$(NORM)$(RESET)"
