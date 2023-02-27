
OUT  = faustlexer.cpp faustparser.cpp faustparser.hpp
YACC = bison
LEX = flex
PREFIX := FAUST
LEX_OPTIONS:= -P$(PREFIX)
YACC_OPTIONS:= -p$(PREFIX)

code : $(OUT)

faustparser.hpp : faustparser.y
faustparser.cpp : faustparser.y
	$(YACC) -d -o faustparser.cpp $(YACC_OPTIONS) faustparser.y

faustlexer.cpp : faustlexer.l
	$(LEX) -I -ofaustlexer.cpp $(LEX_OPTIONS) faustlexer.l

clean:
	rm -f $(OUT)
	