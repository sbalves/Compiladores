FILENAME = gocompiler.l
FILENAME2 = gocompiler.y
FILENAME3 = structures.c
FILENAME4 = structures.h
FILENAME5 = semantic_analysis.c
FILENAME6 = semantic_analysis.h
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

exe: ${FILENAME} ${FILENAME2}
		@echo "$(GREEN)$(BOLD)--------------------$(NORM)$(RESET)$(GREEN)COMPILING$(NORM)$(RESET)$(GREEN)$(BOLD)---------------------$(NORM)$(RESET)$(BLUE)"
		lex ${FILENAME}
		yacc -y -d -v -t ${FILENAME2}
		cc -o ${EXE} -ggdb3 y.tab.c lex.yy.c structures.c semantic_analysis.c auxiliar_functions.c
		valgrind --leak-check=full --show-leak-kinds=all --log-file="valgrind.txt" ./gocompiler < meta3_testes/logical_operators.dgo
		@echo "$(GREEN)$(BOLD)-----------------------$(NORM)$(RESET)$(GREEN)Done$(NORM)$(RESET)$(GREEN)$(BOLD)-----------------------$(NORM)$(RESET)"

clear:
	rm -rf *${EXE}
	rm -rf $(EXE).zip

zip:
	@echo "$(GREEN)$(BOLD)--------------$(NORM)$(RESET)$(GREEN)Compressing $(EXE)$(NORM)$(RESET)$(GREEN)$(BOLD)-------------$(NORM)$(RESET)$(BLUE)"
	zip -r $(EXE).zip ${FILENAME} ${FILENAME2} ${FILENAME3} ${FILENAME4} ${FILENAME5} ${FILENAME6}  
	@echo "$(GREEN)$(BOLD)-----------------------$(NORM)$(RESET)$(GREEN)Done$(NORM)$(RESET)$(GREEN)$(BOLD)----------------------$(NORM)$(RESET)"
