subprojects := boxes errors evaluate generator parser propagate signals tlib draw draw/device draw/schema extended

sources = $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard draw/*/*.cpp)

objects = $(sources:.cpp=.o)

VPATH = $(subprojects)

CXXFLAGS := $(addprefix -I, $(subprojects)) $(CXXFLAGS)
###CXXFLAGS := -g -O0 -Wall $(addprefix -I, $(subprojects))


all : faust

faust : $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o faust


.PHONY: clean depend ctags parser

parser :
	bison -d -o parser/faustparser.cpp parser/faustparser.y
	flex -I -oparser/faustlexer.cpp parser/faustlexer.l

clean :
	rm -f $(objects) faust *.il *.dpi *.spi */*.il */*.dpi */*.spi *~ */*~

depend :
	makedepend -w120 -Y -- $(CXXFLAGS) -- $(sources)

ctags:
	ctags main.cpp boxes/* errors/* evaluate/* generator/* parser/* propagate/* signals/* tlib/* draw/* extended/*

doc: $(wildcard *.cpp) $(wildcard */*.cpp)  $(wildcard */*.h) $(wildcard */*.hh)
	doxygen

# DO NOT DELETE

main.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
main.o: tlib/shlysis.hh tlib/recness.hh signals/binop.hh signals/sigtype.hh tlib/smartpointer.hh
main.o: signals/sigtyperules.hh signals/sigprint.hh generator/simplify.hh generator/privatise.hh
main.o: generator/compile_scal.hh generator/compile.hh generator/klass.hh generator/uitree.hh generator/Text.hh
main.o: generator/description.hh generator/compile_vect.hh propagate/propagate.hh boxes/boxes.hh errors/errormsg.hh
main.o: boxes/ppbox.hh generator/enrobage.hh evaluate/eval.hh parser/sourcereader.hh draw/device/SVGDev.h
main.o: draw/device/device.h draw/schema/schema.h draw/drawschema.hh
boxes/boxcomplexity.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
boxes/boxcomplexity.o: tlib/list.hh tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh
boxes/boxcomplexity.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh
boxes/boxcomplexity.o: boxes/boxcomplexity.h boxes/boxes.hh
boxes/boxes.o: boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
boxes/boxes.o: tlib/shlysis.hh tlib/recness.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh
boxes/boxes.o: signals/sigtype.hh tlib/smartpointer.hh
boxes/boxtype.o: boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
boxes/boxtype.o: tlib/shlysis.hh tlib/recness.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh
boxes/boxtype.o: signals/sigtype.hh tlib/smartpointer.hh extended/xtended.hh generator/klass.hh generator/uitree.hh
boxes/boxtype.o: signals/sigvisitor.hh
boxes/ppbox.o: tlib/list.hh tlib/symbol.hh tlib/tree.hh tlib/node.hh boxes/boxes.hh tlib/tlib.hh tlib/num.hh
boxes/ppbox.o: tlib/shlysis.hh tlib/recness.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh
boxes/ppbox.o: signals/sigtype.hh tlib/smartpointer.hh extended/xtended.hh generator/klass.hh generator/uitree.hh
boxes/ppbox.o: signals/sigvisitor.hh
draw/drawschema.o: boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
draw/drawschema.o: tlib/shlysis.hh tlib/recness.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh
draw/drawschema.o: signals/sigtype.hh tlib/smartpointer.hh draw/device/devLib.h draw/device/SVGDev.h
draw/drawschema.o: draw/device/device.h draw/device/PSDev.h extended/xtended.hh generator/klass.hh generator/uitree.hh
draw/drawschema.o: signals/sigvisitor.hh evaluate/eval.hh parser/sourcereader.hh tlib/occurrences.hh
draw/drawschema.o: boxes/boxcomplexity.h draw/schema/schema.h draw/drawschema.hh
errors/errormsg.o: errors/errormsg.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
errors/errormsg.o: tlib/shlysis.hh tlib/recness.hh boxes/boxes.hh signals/signals.hh signals/binop.hh
evaluate/eval.o: evaluate/eval.hh boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
evaluate/eval.o: tlib/list.hh tlib/shlysis.hh tlib/recness.hh signals/signals.hh signals/binop.hh
evaluate/eval.o: parser/sourcereader.hh errors/errormsg.hh boxes/ppbox.hh generator/simplify.hh propagate/propagate.hh
extended/absprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/absprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/absprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/absprim.o: signals/sigtyperules.hh
extended/acosprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/acosprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/acosprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/asinprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/asinprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/asinprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/atan2prim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
extended/atan2prim.o: tlib/list.hh tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh
extended/atan2prim.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh
extended/atan2prim.o: generator/Text.hh
extended/atanprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/atanprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/atanprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/ceilprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/ceilprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/ceilprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/cosprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/cosprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/cosprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/expprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/expprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/expprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/floorprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
extended/floorprim.o: tlib/list.hh tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh
extended/floorprim.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh
extended/floorprim.o: generator/Text.hh
extended/fmodprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/fmodprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/fmodprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/log10prim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
extended/log10prim.o: tlib/list.hh tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh
extended/log10prim.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh
extended/log10prim.o: generator/Text.hh
extended/logprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/logprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/logprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/maxprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/maxprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/maxprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/maxprim.o: signals/sigtyperules.hh
extended/minprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/minprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/minprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/minprim.o: signals/sigtyperules.hh
extended/powprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/powprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/powprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/remainderprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
extended/remainderprim.o: tlib/list.hh tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh
extended/remainderprim.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh signals/signals.hh
extended/remainderprim.o: signals/binop.hh generator/Text.hh
extended/rintprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/rintprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/rintprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/sinprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/sinprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/sinprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/sqrtprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/sqrtprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/sqrtprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/tanprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/tanprim.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh
extended/tanprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
generator/codegeneration.o: generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh
generator/codegeneration.o: tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh tlib/recness.hh signals/binop.hh
generator/codegeneration.o: generator/klass.hh signals/sigtype.hh tlib/smartpointer.hh generator/uitree.hh
generator/codegeneration.o: generator/Text.hh generator/description.hh signals/sigprint.hh signals/sigtyperules.hh
generator/codegeneration.o: signals/prim2.hh
generator/compile.o: generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh
generator/compile.o: tlib/num.hh tlib/list.hh tlib/shlysis.hh tlib/recness.hh signals/binop.hh generator/klass.hh
generator/compile.o: signals/sigtype.hh tlib/smartpointer.hh generator/uitree.hh generator/Text.hh
generator/compile.o: generator/description.hh signals/sigprint.hh signals/sigtyperules.hh generator/simplify.hh
generator/compile.o: generator/privatise.hh generator/grouper.hh signals/sigvisitor.hh
generator/compile_scal.o: generator/compile_scal.hh generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh
generator/compile_scal.o: tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh tlib/recness.hh
generator/compile_scal.o: signals/binop.hh generator/klass.hh signals/sigtype.hh tlib/smartpointer.hh
generator/compile_scal.o: generator/uitree.hh generator/Text.hh generator/description.hh signals/sigtyperules.hh
generator/compile_scal.o: signals/sigprint.hh generator/simplify.hh generator/privatise.hh signals/prim2.hh
generator/compile_scal.o: extended/xtended.hh signals/sigvisitor.hh
generator/compile_vect.o: generator/compile_vect.hh generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh
generator/compile_vect.o: tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh tlib/recness.hh
generator/compile_vect.o: signals/binop.hh generator/klass.hh signals/sigtype.hh tlib/smartpointer.hh
generator/compile_vect.o: generator/uitree.hh generator/Text.hh generator/description.hh generator/compile_scal.hh
generator/compile_vect.o: signals/sigtyperules.hh signals/sigprint.hh generator/simplify.hh generator/privatise.hh
generator/compile_vect.o: signals/prim2.hh
generator/description.o: generator/description.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh
generator/description.o: tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh tlib/recness.hh signals/binop.hh
generator/description.o: tlib/smartpointer.hh generator/uitree.hh generator/Text.hh
generator/enrobage.o: generator/enrobage.hh
generator/grouper.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
generator/grouper.o: tlib/shlysis.hh tlib/recness.hh signals/binop.hh signals/sigprint.hh signals/sigorderrules.hh
generator/grouper.o: generator/grouper.hh signals/sigvisitor.hh
generator/klass.o: tlib/smartpointer.hh generator/klass.hh signals/sigtype.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh
generator/klass.o: tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh tlib/recness.hh generator/uitree.hh
generator/klass.o: generator/Text.hh signals/signals.hh signals/binop.hh
generator/normalize.o: tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
generator/normalize.o: tlib/recness.hh signals/signals.hh signals/binop.hh signals/sigprint.hh generator/simplify.hh
generator/normalize.o: generator/normalize.hh signals/sigorderrules.hh
generator/privatise.o: signals/sigtype.hh tlib/smartpointer.hh signals/sigprint.hh signals/signals.hh tlib/tlib.hh
generator/privatise.o: tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
generator/privatise.o: tlib/recness.hh signals/binop.hh signals/sigtyperules.hh generator/privatise.hh
generator/sharing.o: generator/compile_vect.hh generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh
generator/sharing.o: tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh tlib/recness.hh
generator/sharing.o: signals/binop.hh generator/klass.hh signals/sigtype.hh tlib/smartpointer.hh generator/uitree.hh
generator/sharing.o: generator/Text.hh generator/description.hh generator/compile_scal.hh signals/sigtyperules.hh
generator/sharing.o: signals/sigprint.hh
generator/simplify.o: signals/sigtype.hh tlib/smartpointer.hh signals/sigtyperules.hh signals/signals.hh tlib/tlib.hh
generator/simplify.o: tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh tlib/recness.hh
generator/simplify.o: signals/binop.hh signals/sigorderrules.hh signals/sigprint.hh generator/simplify.hh
generator/simplify.o: extended/xtended.hh generator/klass.hh generator/uitree.hh signals/sigvisitor.hh
generator/simplify.o: generator/normalize.hh
generator/Text.o: generator/Text.hh
generator/uitree.o: generator/uitree.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
generator/uitree.o: tlib/shlysis.hh tlib/recness.hh
parser/faustlexer.o: tlib/tree.hh tlib/symbol.hh tlib/node.hh parser/faustparser.hpp
parser/faustparser.o: tlib/tree.hh tlib/symbol.hh tlib/node.hh extended/xtended.hh tlib/tlib.hh tlib/num.hh
parser/faustparser.o: tlib/list.hh tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh
parser/faustparser.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh
parser/faustparser.o: boxes/boxes.hh signals/prim2.hh errors/errormsg.hh
parser/sourcereader.o: parser/sourcereader.hh boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh
parser/sourcereader.o: tlib/num.hh tlib/list.hh tlib/shlysis.hh tlib/recness.hh signals/signals.hh signals/binop.hh
parser/sourcereader.o: generator/enrobage.hh
propagate/propagate.o: propagate/propagate.hh boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh
propagate/propagate.o: tlib/num.hh tlib/list.hh tlib/shlysis.hh tlib/recness.hh signals/signals.hh signals/binop.hh
propagate/propagate.o: signals/prim2.hh signals/sigtype.hh tlib/smartpointer.hh boxes/ppbox.hh extended/xtended.hh
propagate/propagate.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh
signals/binop.o: signals/binop.hh tlib/node.hh tlib/symbol.hh
signals/prim2.o: signals/prim2.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
signals/prim2.o: tlib/shlysis.hh tlib/recness.hh signals/sigtype.hh tlib/smartpointer.hh
signals/signals.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
signals/signals.o: tlib/shlysis.hh tlib/recness.hh signals/binop.hh
signals/sigorderrules.o: signals/sigtype.hh tlib/smartpointer.hh signals/sigprint.hh signals/signals.hh tlib/tlib.hh
signals/sigorderrules.o: tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
signals/sigorderrules.o: tlib/recness.hh signals/binop.hh signals/prim2.hh signals/sigorderrules.hh extended/xtended.hh
signals/sigorderrules.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh
signals/sigprint.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
signals/sigprint.o: tlib/shlysis.hh tlib/recness.hh signals/binop.hh signals/sigtype.hh tlib/smartpointer.hh
signals/sigprint.o: signals/sigtyperules.hh
signals/sigtype.o: signals/sigtype.hh tlib/smartpointer.hh
signals/sigtyperules.o: signals/sigtype.hh tlib/smartpointer.hh signals/sigprint.hh signals/signals.hh tlib/tlib.hh
signals/sigtyperules.o: tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
signals/sigtyperules.o: tlib/recness.hh signals/binop.hh signals/prim2.hh signals/sigtyperules.hh extended/xtended.hh
signals/sigtyperules.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh
signals/sigvisitor.o: signals/sigvisitor.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh
signals/sigvisitor.o: tlib/num.hh tlib/list.hh tlib/shlysis.hh tlib/recness.hh signals/binop.hh extended/xtended.hh
signals/sigvisitor.o: signals/sigtype.hh tlib/smartpointer.hh generator/klass.hh generator/uitree.hh
tlib/list.o: tlib/list.hh tlib/symbol.hh tlib/tree.hh tlib/node.hh
tlib/node.o: tlib/node.hh tlib/symbol.hh
tlib/occurrences.o: tlib/occurrences.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
tlib/occurrences.o: tlib/shlysis.hh tlib/recness.hh
tlib/recness.o: tlib/recness.hh tlib/tree.hh tlib/symbol.hh tlib/node.hh tlib/list.hh
tlib/recursive-tree.o: tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
tlib/recursive-tree.o: tlib/recness.hh
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
