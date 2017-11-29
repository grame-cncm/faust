
OUT  = faustlexer.cpp faustparser.cpp faustparser.hpp
YACC = bison
LEX = flex
PREFIX := FAUST
#OPTIONS:= -I -P$(PREFIX)

code : $(OUT)

faustparser.cpp : faustparser.y
	$(YACC) -d -o faustparser.cpp $(OPTIONS) faustparser.y

faustlexer.cpp : faustlexer.l
	$(LEX) -I -ofaustlexer.cpp $(OPTIONS) faustlexer.l

