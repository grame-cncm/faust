subprojects := boxes errors evaluate generator normalize parser propagate signals tlib draw draw/device draw/schema extended

sources = $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard draw/*/*.cpp)

objects = $(sources:.cpp=.o)

VPATH = $(subprojects)

CXXFLAGS := -g -O0 -ffriend-injection $(addprefix -I, $(subprojects))


all : faust

faust : $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o faust


.PHONY: clean depend ctags parser

parser :
	bison -d -o parser/faustparser.cpp parser/faustparser.y
	flex -I -oparser/faustlexer.cpp parser/faustlexer.l

clean :
	rm -f $(objects) faust *.il *.dpi *.spi */*.il */*.dpi */*.spi *~ */*~
	rm -rf doc

depend :
	makedepend -w120 -Y -- $(CXXFLAGS) -- $(sources)

ctags:
	ctags main.cpp boxes/* errors/* evaluate/* generator/* normalize/* parser/* propagate/* signals/* tlib/* draw/* extended/*

doc: $(wildcard *.cpp) $(wildcard */*.cpp)  $(wildcard */*.h) $(wildcard */*.hh)
	doxygen

# DO NOT DELETE

main.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
main.o: tlib/shlysis.hh signals/binop.hh signals/sigtype.hh tlib/smartpointer.hh signals/sigtyperules.hh
main.o: signals/sigprint.hh normalize/simplify.hh normalize/privatise.hh generator/compile_scal.hh generator/compile.hh
main.o: generator/klass.hh generator/uitree.hh generator/Text.hh generator/description.hh generator/occurences.hh
main.o: generator/compile_vect.hh propagate/propagate.hh boxes/boxes.hh errors/errormsg.hh boxes/ppbox.hh
main.o: generator/enrobage.hh evaluate/eval.hh parser/sourcereader.hh draw/schema/schema.h draw/device/device.h
main.o: draw/drawschema.hh
boxes/boxcomplexity.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
boxes/boxcomplexity.o: tlib/list.hh tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
boxes/boxcomplexity.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh
boxes/boxcomplexity.o: boxes/boxcomplexity.h boxes/boxes.hh
boxes/boxes.o: boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
boxes/boxes.o: tlib/shlysis.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh signals/sigtype.hh
boxes/boxes.o: tlib/smartpointer.hh
boxes/boxtype.o: boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
boxes/boxtype.o: tlib/shlysis.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh signals/sigtype.hh
boxes/boxtype.o: tlib/smartpointer.hh extended/xtended.hh generator/klass.hh generator/uitree.hh signals/sigvisitor.hh
boxes/ppbox.o: tlib/list.hh tlib/symbol.hh tlib/tree.hh tlib/node.hh boxes/boxes.hh tlib/tlib.hh tlib/num.hh
boxes/ppbox.o: tlib/shlysis.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh signals/sigtype.hh
boxes/ppbox.o: tlib/smartpointer.hh extended/xtended.hh generator/klass.hh generator/uitree.hh signals/sigvisitor.hh
draw/drawschema.o: boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
draw/drawschema.o: tlib/shlysis.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh
draw/drawschema.o: signals/sigtype.hh tlib/smartpointer.hh draw/device/devLib.h draw/device/SVGDev.h
draw/drawschema.o: draw/device/device.h draw/device/PSDev.h extended/xtended.hh generator/klass.hh generator/uitree.hh
draw/drawschema.o: signals/sigvisitor.hh evaluate/eval.hh parser/sourcereader.hh tlib/occurrences.hh
draw/drawschema.o: boxes/boxcomplexity.h draw/schema/schema.h draw/drawschema.hh
errors/errormsg.o: errors/errormsg.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
errors/errormsg.o: tlib/shlysis.hh boxes/boxes.hh signals/signals.hh signals/binop.hh
evaluate/eval.o: evaluate/eval.hh boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
evaluate/eval.o: tlib/list.hh tlib/shlysis.hh signals/signals.hh signals/binop.hh parser/sourcereader.hh
evaluate/eval.o: errors/errormsg.hh boxes/ppbox.hh normalize/simplify.hh propagate/propagate.hh
extended/absprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/absprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/absprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh signals/sigtyperules.hh
extended/acosprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/acosprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/acosprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/asinprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/asinprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/asinprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/atan2prim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
extended/atan2prim.o: tlib/list.hh tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/atan2prim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/atanprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/atanprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/atanprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/ceilprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/ceilprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/ceilprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/cosprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/cosprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/cosprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/expprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/expprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/expprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/floorprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
extended/floorprim.o: tlib/list.hh tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/floorprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/fmodprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/fmodprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/fmodprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/log10prim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
extended/log10prim.o: tlib/list.hh tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/log10prim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/logprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/logprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/logprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/maxprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/maxprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/maxprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh signals/sigtyperules.hh
extended/minprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/minprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/minprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh signals/sigtyperules.hh
extended/powprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/powprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/powprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/remainderprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
extended/remainderprim.o: tlib/list.hh tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/remainderprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh
extended/remainderprim.o: generator/Text.hh
extended/rintprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/rintprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/rintprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/sinprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/sinprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/sinprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/sqrtprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/sqrtprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/sqrtprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/tanprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/tanprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
extended/tanprim.o: signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
generator/codegeneration.o: generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh
generator/codegeneration.o: tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh generator/klass.hh
generator/codegeneration.o: signals/sigtype.hh tlib/smartpointer.hh generator/uitree.hh generator/Text.hh
generator/codegeneration.o: generator/description.hh signals/sigprint.hh signals/sigtyperules.hh signals/prim2.hh
generator/compile.o: generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh
generator/compile.o: tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh generator/klass.hh signals/sigtype.hh
generator/compile.o: tlib/smartpointer.hh generator/uitree.hh generator/Text.hh generator/description.hh
generator/compile.o: signals/sigprint.hh signals/sigtyperules.hh normalize/simplify.hh normalize/privatise.hh
generator/compile_scal.o: generator/compile_scal.hh generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh
generator/compile_scal.o: tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh
generator/compile_scal.o: generator/klass.hh signals/sigtype.hh tlib/smartpointer.hh generator/uitree.hh
generator/compile_scal.o: generator/Text.hh generator/description.hh signals/sigtyperules.hh generator/occurences.hh
generator/compile_scal.o: signals/sigprint.hh signals/recursivness.hh normalize/simplify.hh normalize/privatise.hh
generator/compile_scal.o: signals/prim2.hh extended/xtended.hh signals/sigvisitor.hh generator/contextor.hh
generator/compile_vect.o: generator/compile_vect.hh generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh
generator/compile_vect.o: tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh
generator/compile_vect.o: generator/klass.hh signals/sigtype.hh tlib/smartpointer.hh generator/uitree.hh
generator/compile_vect.o: generator/Text.hh generator/description.hh generator/compile_scal.hh signals/sigtyperules.hh
generator/compile_vect.o: generator/occurences.hh signals/sigprint.hh normalize/simplify.hh normalize/privatise.hh
generator/compile_vect.o: signals/prim2.hh
generator/contextor.o: generator/contextor.hh
generator/description.o: generator/description.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh
generator/description.o: tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh tlib/smartpointer.hh
generator/description.o: generator/uitree.hh generator/Text.hh
generator/enrobage.o: generator/enrobage.hh
generator/klass.o: tlib/smartpointer.hh generator/klass.hh signals/sigtype.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh
generator/klass.o: tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh generator/uitree.hh generator/Text.hh
generator/klass.o: signals/signals.hh signals/binop.hh
generator/occurences.o: signals/recursivness.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh
generator/occurences.o: tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh generator/occurences.hh
generator/occurences.o: signals/sigtype.hh tlib/smartpointer.hh signals/sigtyperules.hh
generator/sharing.o: generator/compile_vect.hh generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh
generator/sharing.o: tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh
generator/sharing.o: generator/klass.hh signals/sigtype.hh tlib/smartpointer.hh generator/uitree.hh generator/Text.hh
generator/sharing.o: generator/description.hh generator/compile_scal.hh signals/sigtyperules.hh generator/occurences.hh
generator/sharing.o: signals/sigprint.hh
generator/Text.o: generator/Text.hh
generator/uitree.o: generator/uitree.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
generator/uitree.o: tlib/shlysis.hh
normalize/normalize.o: tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
normalize/normalize.o: signals/signals.hh signals/binop.hh signals/sigprint.hh normalize/simplify.hh
normalize/normalize.o: normalize/normalize.hh signals/sigorderrules.hh
normalize/privatise.o: signals/sigtype.hh tlib/smartpointer.hh signals/sigprint.hh signals/signals.hh tlib/tlib.hh
normalize/privatise.o: tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
normalize/privatise.o: signals/binop.hh signals/sigtyperules.hh normalize/privatise.hh
normalize/simplify.o: signals/sigtype.hh tlib/smartpointer.hh signals/sigtyperules.hh signals/signals.hh tlib/tlib.hh
normalize/simplify.o: tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
normalize/simplify.o: signals/binop.hh signals/sigorderrules.hh signals/sigprint.hh normalize/simplify.hh
normalize/simplify.o: extended/xtended.hh generator/klass.hh generator/uitree.hh signals/sigvisitor.hh
normalize/simplify.o: normalize/normalize.hh
parser/faustlexer.o: tlib/tree.hh tlib/symbol.hh tlib/node.hh parser/faustparser.hpp
parser/faustparser.o: tlib/tree.hh tlib/symbol.hh tlib/node.hh extended/xtended.hh tlib/tlib.hh tlib/num.hh
parser/faustparser.o: tlib/list.hh tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
parser/faustparser.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh boxes/boxes.hh
parser/faustparser.o: signals/prim2.hh errors/errormsg.hh
parser/sourcereader.o: parser/sourcereader.hh boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh
parser/sourcereader.o: tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/signals.hh signals/binop.hh
parser/sourcereader.o: generator/enrobage.hh
propagate/propagate.o: propagate/propagate.hh boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh
propagate/propagate.o: tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/signals.hh signals/binop.hh signals/prim2.hh
propagate/propagate.o: signals/sigtype.hh tlib/smartpointer.hh boxes/ppbox.hh extended/xtended.hh generator/klass.hh
propagate/propagate.o: generator/uitree.hh signals/sigvisitor.hh
signals/binop.o: signals/binop.hh tlib/node.hh tlib/symbol.hh
signals/prim2.o: signals/prim2.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
signals/prim2.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh
signals/recursivness.o: signals/recursivness.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh
signals/recursivness.o: tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh
signals/signals.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
signals/signals.o: tlib/shlysis.hh signals/binop.hh
signals/sigorderrules.o: signals/sigtype.hh tlib/smartpointer.hh signals/sigprint.hh signals/signals.hh tlib/tlib.hh
signals/sigorderrules.o: tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
signals/sigorderrules.o: signals/binop.hh signals/prim2.hh signals/sigorderrules.hh extended/xtended.hh
signals/sigorderrules.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh
signals/sigprint.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
signals/sigprint.o: tlib/shlysis.hh signals/binop.hh signals/sigtype.hh tlib/smartpointer.hh signals/sigtyperules.hh
signals/sigtype.o: signals/sigtype.hh tlib/smartpointer.hh
signals/sigtyperules.o: signals/sigtype.hh tlib/smartpointer.hh signals/sigprint.hh signals/signals.hh tlib/tlib.hh
signals/sigtyperules.o: tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
signals/sigtyperules.o: signals/binop.hh signals/prim2.hh signals/sigtyperules.hh extended/xtended.hh
signals/sigtyperules.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh
signals/sigvisitor.o: signals/sigvisitor.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh
signals/sigvisitor.o: tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh extended/xtended.hh signals/sigtype.hh
signals/sigvisitor.o: tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
signals/subsignals.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
signals/subsignals.o: tlib/shlysis.hh signals/binop.hh
tlib/list.o: tlib/list.hh tlib/symbol.hh tlib/tree.hh tlib/node.hh
tlib/node.o: tlib/node.hh tlib/symbol.hh
tlib/occurrences.o: tlib/occurrences.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
tlib/occurrences.o: tlib/shlysis.hh
tlib/recursive-tree.o: tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
tlib/shlysis.o: tlib/shlysis.hh tlib/list.hh tlib/symbol.hh tlib/tree.hh tlib/node.hh
tlib/symbol.o: tlib/symbol.hh
tlib/tree.o: tlib/tree.hh tlib/symbol.hh tlib/node.hh
draw/device/PSDev.o: draw/device/PSDev.h draw/device/device.h
draw/device/SVGDev.o: draw/device/SVGDev.h draw/device/device.h
draw/schema/blockSchema.o: draw/schema/blockSchema.h draw/schema/schema.h draw/device/device.h
draw/schema/cableSchema.o: draw/schema/cableSchema.h draw/schema/schema.h draw/device/device.h
draw/schema/cutSchema.o: draw/schema/cutSchema.h draw/schema/schema.h draw/device/device.h
draw/schema/decorateSchema.o: draw/schema/decorateSchema.h draw/schema/schema.h draw/device/device.h
draw/schema/enlargedSchema.o: draw/schema/enlargedSchema.h draw/schema/schema.h draw/device/device.h
draw/schema/mergeSchema.o: draw/schema/mergeSchema.h draw/schema/schema.h draw/device/device.h
draw/schema/parSchema.o: draw/schema/parSchema.h draw/schema/schema.h draw/device/device.h
draw/schema/recSchema.o: draw/schema/recSchema.h draw/schema/schema.h draw/device/device.h
draw/schema/seqSchema.o: draw/schema/seqSchema.h draw/schema/schema.h draw/device/device.h
draw/schema/splitSchema.o: draw/schema/splitSchema.h draw/schema/schema.h draw/device/device.h
draw/schema/topSchema.o: draw/schema/topSchema.h draw/schema/schema.h draw/device/device.h
