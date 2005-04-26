subprojects := boxes errors evaluate generator parser propagate signals tlib draw

sources := $(wildcard *.cpp) $(wildcard */*.cpp)

objects := $(sources:.cpp=.o) parser/faustparser.o parser/faustlexer.o

VPATH := $(subprojects)

CXXFLAGS := -O3 $(addprefix -I, $(subprojects)) $(CXXFLAGS)


all : faust

faust : $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o faust
	
#cancel implicit rules for yacc and lex

%.c : %.y
%.c : %.l

#create new implicit rules

%.cpp %.hpp: %.y
	bison -d -o $@ $<
	
%.cpp : %.l faustparser.hpp
	flex -I -o$@ $<



.PHONY: clean depend ctags

clean :
	rm -f $(objects) faust *.il *.dpi *.spi */*.il */*.dpi */*.spi
	
depend :
	makedepend -w120 -Y -- $(CXXFLAGS) -- $(sources)
	
ctags:
	ctags main.cpp boxes/* errors/* evaluate/* generator/* parser/* propagate/* signals/* tlib/* draw/*

dox:
	doxygen	
	
# DO NOT DELETE

main.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
main.o: tlib/shlysis.hh signals/binop.hh signals/sigtype.hh tlib/smartpointer.hh signals/sigtyperules.hh
main.o: signals/sigprint.hh generator/simplify.hh generator/privatise.hh generator/compile_scal.hh generator/compile.hh
main.o: generator/klass.hh generator/uitree.hh generator/Text.hh generator/compile_vect.hh propagate/propagate.hh
main.o: boxes/boxes.hh errors/errormsg.hh boxes/ppbox.hh generator/enrobage.hh evaluate/eval.hh draw/drawblock.hh
boxes/boxes.o: boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
boxes/boxes.o: tlib/shlysis.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh signals/sigtype.hh
boxes/boxes.o: tlib/smartpointer.hh
boxes/boxtype.o: boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
boxes/boxtype.o: tlib/shlysis.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh signals/sigtype.hh
boxes/boxtype.o: tlib/smartpointer.hh
boxes/ppbox.o: tlib/list.hh tlib/symbol.hh tlib/tree.hh tlib/node.hh boxes/boxes.hh tlib/tlib.hh tlib/num.hh
boxes/ppbox.o: tlib/shlysis.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh signals/sigtype.hh
boxes/ppbox.o: tlib/smartpointer.hh
draw/constrFonctions.o: draw/constrFonctions.h draw/reprLib.h draw/representation.h draw/device.h draw/wire.h
draw/constrFonctions.o: draw/reprBloc.h draw/reprPara.h draw/reprSerie.h draw/reprRecurs.h draw/reprSplit.h
draw/constrFonctions.o: draw/reprMerge.h draw/reprGroup.h draw/reprParam.h draw/devLib.h draw/SVGDev.h draw/PSDev.h
draw/constrFonctions.o: draw/treeLib.h draw/treeRepr.h draw/treeBloc.h draw/treeNormal.h draw/treeGroup.h
draw/constrFonctions.o: draw/treeParam.h
draw/drawbloc.o: boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
draw/drawbloc.o: tlib/shlysis.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh signals/sigtype.hh
draw/drawbloc.o: tlib/smartpointer.hh draw/reprLib.h draw/representation.h draw/device.h draw/wire.h draw/reprBloc.h
draw/drawbloc.o: draw/reprPara.h draw/reprSerie.h draw/reprRecurs.h draw/reprSplit.h draw/reprMerge.h draw/reprGroup.h
draw/drawbloc.o: draw/reprParam.h draw/devLib.h draw/SVGDev.h draw/PSDev.h draw/treeLib.h draw/treeRepr.h
draw/drawbloc.o: draw/treeBloc.h draw/treeNormal.h draw/treeGroup.h draw/treeParam.h draw/drawblock.hh
draw/drawbloc.o: draw/constrFonctions.h
draw/PSDev.o: draw/PSDev.h draw/device.h
draw/reprBloc.o: draw/reprBloc.h draw/representation.h draw/device.h draw/wire.h
draw/representation.o: draw/representation.h draw/device.h draw/wire.h
draw/reprGroup.o: draw/reprGroup.h draw/representation.h draw/device.h draw/wire.h
draw/reprMerge.o: draw/reprMerge.h draw/representation.h draw/device.h draw/wire.h
draw/reprPara.o: draw/reprPara.h draw/representation.h draw/device.h draw/wire.h
draw/reprParam.o: draw/reprParam.h draw/representation.h draw/device.h draw/wire.h
draw/reprRecurs.o: draw/reprRecurs.h draw/representation.h draw/device.h draw/wire.h
draw/reprSerie.o: draw/reprSerie.h draw/representation.h draw/device.h draw/wire.h
draw/reprSplit.o: draw/reprSplit.h draw/representation.h draw/device.h draw/wire.h
draw/SVGDev.o: draw/SVGDev.h draw/device.h
draw/treeBloc.o: draw/treeBloc.h draw/treeRepr.h draw/representation.h draw/device.h draw/wire.h draw/reprLib.h
draw/treeBloc.o: draw/reprBloc.h draw/reprPara.h draw/reprSerie.h draw/reprRecurs.h draw/reprSplit.h draw/reprMerge.h
draw/treeBloc.o: draw/reprGroup.h draw/reprParam.h
draw/treeGroup.o: draw/treeGroup.h draw/treeRepr.h draw/representation.h draw/device.h draw/wire.h draw/reprLib.h
draw/treeGroup.o: draw/reprBloc.h draw/reprPara.h draw/reprSerie.h draw/reprRecurs.h draw/reprSplit.h draw/reprMerge.h
draw/treeGroup.o: draw/reprGroup.h draw/reprParam.h
draw/treeNormal.o: draw/treeNormal.h draw/treeRepr.h draw/representation.h draw/device.h draw/wire.h draw/reprLib.h
draw/treeNormal.o: draw/reprBloc.h draw/reprPara.h draw/reprSerie.h draw/reprRecurs.h draw/reprSplit.h draw/reprMerge.h
draw/treeNormal.o: draw/reprGroup.h draw/reprParam.h
draw/treeParam.o: draw/treeParam.h draw/treeRepr.h draw/representation.h draw/device.h draw/wire.h draw/reprLib.h
draw/treeParam.o: draw/reprBloc.h draw/reprPara.h draw/reprSerie.h draw/reprRecurs.h draw/reprSplit.h draw/reprMerge.h
draw/treeParam.o: draw/reprGroup.h draw/reprParam.h
draw/wire.o: draw/wire.h draw/device.h
errors/errormsg.o: errors/errormsg.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
errors/errormsg.o: tlib/shlysis.hh boxes/boxes.hh signals/signals.hh signals/binop.hh
evaluate/eval.o: evaluate/eval.hh boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
evaluate/eval.o: tlib/list.hh tlib/shlysis.hh signals/signals.hh signals/binop.hh errors/errormsg.hh boxes/ppbox.hh
evaluate/eval.o: generator/simplify.hh propagate/propagate.hh
generator/codegeneration.o: generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh
generator/codegeneration.o: tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh generator/klass.hh
generator/codegeneration.o: signals/sigtype.hh tlib/smartpointer.hh generator/uitree.hh generator/Text.hh
generator/codegeneration.o: signals/sigprint.hh signals/sigtyperules.hh signals/prim2.hh
generator/compile.o: generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh
generator/compile.o: tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh generator/klass.hh signals/sigtype.hh
generator/compile.o: tlib/smartpointer.hh generator/uitree.hh generator/Text.hh signals/sigprint.hh
generator/compile.o: signals/sigtyperules.hh generator/simplify.hh generator/privatise.hh
generator/compile_scal.o: generator/compile_scal.hh generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh
generator/compile_scal.o: tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh
generator/compile_scal.o: generator/klass.hh signals/sigtype.hh tlib/smartpointer.hh generator/uitree.hh
generator/compile_scal.o: generator/Text.hh signals/sigtyperules.hh signals/sigprint.hh generator/simplify.hh
generator/compile_scal.o: generator/privatise.hh signals/prim2.hh
generator/compile_vect.o: generator/compile_vect.hh generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh
generator/compile_vect.o: tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh
generator/compile_vect.o: generator/klass.hh signals/sigtype.hh tlib/smartpointer.hh generator/uitree.hh
generator/compile_vect.o: generator/Text.hh generator/compile_scal.hh signals/sigtyperules.hh signals/sigprint.hh
generator/compile_vect.o: generator/simplify.hh generator/privatise.hh signals/prim2.hh
generator/enrobage.o: generator/enrobage.hh
generator/klass.o: tlib/smartpointer.hh generator/klass.hh signals/sigtype.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh
generator/klass.o: tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh generator/uitree.hh generator/Text.hh
generator/klass.o: signals/signals.hh signals/binop.hh
generator/normalize.o: tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
generator/normalize.o: signals/signals.hh signals/binop.hh signals/sigprint.hh generator/simplify.hh
generator/normalize.o: generator/normalize.hh signals/sigorderrules.hh
generator/privatise.o: signals/sigtype.hh tlib/smartpointer.hh signals/sigprint.hh signals/signals.hh tlib/tlib.hh
generator/privatise.o: tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
generator/privatise.o: signals/binop.hh signals/sigtyperules.hh generator/privatise.hh
generator/sharing.o: generator/compile_vect.hh generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh
generator/sharing.o: tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh
generator/sharing.o: generator/klass.hh signals/sigtype.hh tlib/smartpointer.hh generator/uitree.hh generator/Text.hh
generator/sharing.o: generator/compile_scal.hh signals/sigtyperules.hh signals/sigprint.hh
generator/simplify.o: signals/sigtype.hh tlib/smartpointer.hh signals/sigtyperules.hh signals/signals.hh tlib/tlib.hh
generator/simplify.o: tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
generator/simplify.o: signals/binop.hh signals/sigorderrules.hh signals/sigprint.hh generator/simplify.hh
generator/simplify.o: generator/normalize.hh
generator/Text.o: generator/Text.hh
generator/uitree.o: generator/uitree.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
generator/uitree.o: tlib/shlysis.hh
propagate/propagate.o: propagate/propagate.hh boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh
propagate/propagate.o: tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/signals.hh signals/binop.hh signals/prim2.hh
propagate/propagate.o: signals/sigtype.hh tlib/smartpointer.hh
signals/binop.o: signals/binop.hh tlib/node.hh tlib/symbol.hh
signals/prim2.o: signals/prim2.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
signals/prim2.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh
signals/signals.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
signals/signals.o: tlib/shlysis.hh signals/binop.hh
signals/sigorderrules.o: signals/sigtype.hh tlib/smartpointer.hh signals/sigprint.hh signals/signals.hh tlib/tlib.hh
signals/sigorderrules.o: tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
signals/sigorderrules.o: signals/binop.hh signals/prim2.hh signals/sigorderrules.hh
signals/sigprint.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
signals/sigprint.o: tlib/shlysis.hh signals/binop.hh signals/sigtype.hh tlib/smartpointer.hh signals/sigtyperules.hh
signals/sigtype.o: signals/sigtype.hh tlib/smartpointer.hh
signals/sigtyperules.o: signals/sigtype.hh tlib/smartpointer.hh signals/sigprint.hh signals/signals.hh tlib/tlib.hh
signals/sigtyperules.o: tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
signals/sigtyperules.o: signals/binop.hh signals/prim2.hh signals/sigtyperules.hh
tlib/list.o: tlib/list.hh tlib/symbol.hh tlib/tree.hh tlib/node.hh
tlib/recursive-tree.o: tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
tlib/shlysis.o: tlib/shlysis.hh tlib/list.hh tlib/symbol.hh tlib/tree.hh tlib/node.hh
tlib/symbol.o: tlib/symbol.hh
tlib/tree.o: tlib/tree.hh tlib/symbol.hh tlib/node.hh
