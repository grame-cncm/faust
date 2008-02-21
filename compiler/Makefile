subprojects := boxes errors evaluate generator normalize parser propagate parallelize signals tlib draw draw/device draw/schema extended patternmatcher

sources = $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard draw/*/*.cpp)

objects = $(sources:.cpp=.o)

VPATH = $(subprojects)

CXXFLAGS := -g -O3 -Wall -Wuninitialized $(addprefix -I, $(subprojects))


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
	ctags -R main.cpp $(subprojects)

doc: $(wildcard *.cpp) $(wildcard */*.cpp)  $(wildcard */*.h) $(wildcard */*.hh)
	doxygen

# DO NOT DELETE

main.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
main.o: tlib/shlysis.hh signals/binop.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh
main.o: signals/sigtyperules.hh signals/sigprint.hh normalize/simplify.hh normalize/privatise.hh
main.o: generator/compile_scal.hh generator/compile.hh generator/klass.hh generator/uitree.hh generator/Text.hh
main.o: generator/description.hh generator/occurences.hh tlib/property.hh generator/compile_vect.hh parallelize/loop.hh
main.o: propagate/propagate.hh boxes/boxes.hh errors/errormsg.hh boxes/ppbox.hh parser/enrobage.hh evaluate/eval.hh
main.o: parser/sourcereader.hh draw/schema/schema.h draw/device/device.h draw/drawschema.hh
boxes/boxcomplexity.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
boxes/boxcomplexity.o: tlib/list.hh tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh
boxes/boxcomplexity.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh
boxes/boxcomplexity.o: boxes/boxcomplexity.h boxes/boxes.hh
boxes/boxes.o: boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
boxes/boxes.o: tlib/shlysis.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh signals/sigtype.hh
boxes/boxes.o: tlib/smartpointer.hh signals/interval.hh
boxes/boxtype.o: boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
boxes/boxtype.o: tlib/shlysis.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh signals/sigtype.hh
boxes/boxtype.o: tlib/smartpointer.hh signals/interval.hh extended/xtended.hh generator/klass.hh generator/uitree.hh
boxes/boxtype.o: signals/sigvisitor.hh
boxes/ppbox.o: tlib/list.hh tlib/symbol.hh tlib/tree.hh tlib/node.hh boxes/boxes.hh tlib/tlib.hh tlib/num.hh
boxes/ppbox.o: tlib/shlysis.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh signals/sigtype.hh
boxes/ppbox.o: tlib/smartpointer.hh signals/interval.hh extended/xtended.hh generator/klass.hh generator/uitree.hh
boxes/ppbox.o: signals/sigvisitor.hh
draw/drawschema.o: boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
draw/drawschema.o: tlib/shlysis.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh signals/prim2.hh
draw/drawschema.o: signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh draw/device/devLib.h
draw/drawschema.o: draw/device/SVGDev.h draw/device/device.h draw/device/PSDev.h extended/xtended.hh generator/klass.hh
draw/drawschema.o: generator/uitree.hh signals/sigvisitor.hh evaluate/eval.hh parser/sourcereader.hh
draw/drawschema.o: tlib/occurrences.hh boxes/boxcomplexity.h draw/schema/schema.h draw/drawschema.hh
draw/drawschema.o: tlib/compatibility.hh parser/unistd.h /usr/include/unistd.h
errors/errormsg.o: errors/errormsg.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
errors/errormsg.o: tlib/shlysis.hh boxes/boxes.hh signals/signals.hh signals/binop.hh
evaluate/eval.o: evaluate/eval.hh boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
evaluate/eval.o: tlib/list.hh tlib/shlysis.hh signals/signals.hh signals/binop.hh parser/sourcereader.hh
evaluate/eval.o: errors/errormsg.hh boxes/ppbox.hh normalize/simplify.hh propagate/propagate.hh
evaluate/eval.o: patternmatcher/patternmatcher.hh extended/xtended.hh signals/sigtype.hh tlib/smartpointer.hh
evaluate/eval.o: signals/interval.hh generator/klass.hh generator/uitree.hh signals/sigvisitor.hh
evaluate/eval.o: evaluate/loopDetector.hh
evaluate/loopDetector.o: evaluate/loopDetector.hh boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh
evaluate/loopDetector.o: tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/signals.hh signals/binop.hh
evaluate/loopDetector.o: parser/sourcereader.hh boxes/ppbox.hh
extended/absprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/absprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/absprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/absprim.o: signals/sigtyperules.hh
extended/acosprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/acosprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/acosprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/asinprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/asinprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/asinprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/atan2prim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
extended/atan2prim.o: tlib/list.hh tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh
extended/atan2prim.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh
extended/atan2prim.o: generator/Text.hh
extended/atanprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/atanprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/atanprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/ceilprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/ceilprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/ceilprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/cosprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/cosprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/cosprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/expprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/expprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/expprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/floorprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
extended/floorprim.o: tlib/list.hh tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh
extended/floorprim.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh
extended/floorprim.o: generator/Text.hh
extended/fmodprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/fmodprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/fmodprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/log10prim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
extended/log10prim.o: tlib/list.hh tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh
extended/log10prim.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh
extended/log10prim.o: generator/Text.hh
extended/logprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/logprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/logprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/maxprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/maxprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/maxprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/maxprim.o: signals/sigtyperules.hh
extended/minprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/minprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/minprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/minprim.o: signals/sigtyperules.hh
extended/powprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/powprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/powprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/remainderprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
extended/remainderprim.o: tlib/list.hh tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh
extended/remainderprim.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh signals/signals.hh
extended/remainderprim.o: signals/binop.hh tlib/compatibility.hh parser/unistd.h /usr/include/unistd.h
extended/remainderprim.o: generator/Text.hh
extended/rintprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/rintprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/rintprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh
extended/rintprim.o: tlib/compatibility.hh parser/unistd.h /usr/include/unistd.h generator/Text.hh
extended/sinprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/sinprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/sinprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/sqrtprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/sqrtprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/sqrtprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
extended/tanprim.o: extended/xtended.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
extended/tanprim.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/klass.hh
extended/tanprim.o: generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh generator/Text.hh
generator/codegeneration.o: generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh
generator/codegeneration.o: tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh generator/klass.hh
generator/codegeneration.o: signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh generator/uitree.hh
generator/codegeneration.o: generator/Text.hh generator/description.hh signals/sigprint.hh signals/sigtyperules.hh
generator/codegeneration.o: signals/prim2.hh
generator/compile.o: generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh
generator/compile.o: tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh generator/klass.hh signals/sigtype.hh
generator/compile.o: tlib/smartpointer.hh signals/interval.hh generator/uitree.hh generator/Text.hh
generator/compile.o: generator/description.hh signals/sigprint.hh signals/sigtyperules.hh normalize/simplify.hh
generator/compile.o: normalize/privatise.hh
generator/compile_scal.o: generator/compile_scal.hh generator/compile.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh
generator/compile_scal.o: tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh
generator/compile_scal.o: generator/klass.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh
generator/compile_scal.o: generator/uitree.hh generator/Text.hh generator/description.hh signals/sigtyperules.hh
generator/compile_scal.o: generator/occurences.hh tlib/property.hh signals/sigprint.hh signals/recursivness.hh
generator/compile_scal.o: normalize/simplify.hh normalize/privatise.hh signals/prim2.hh extended/xtended.hh
generator/compile_scal.o: signals/sigvisitor.hh tlib/compatibility.hh parser/unistd.h /usr/include/unistd.h
generator/compile_scal.o: signals/ppsig.hh
generator/compile_vect.o: generator/compile_vect.hh generator/compile_scal.hh generator/compile.hh signals/signals.hh
generator/compile_vect.o: tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
generator/compile_vect.o: tlib/shlysis.hh signals/binop.hh generator/klass.hh signals/sigtype.hh tlib/smartpointer.hh
generator/compile_vect.o: signals/interval.hh generator/uitree.hh generator/Text.hh generator/description.hh
generator/compile_vect.o: signals/sigtyperules.hh generator/occurences.hh tlib/property.hh parallelize/loop.hh
generator/compile_vect.o: signals/ppsig.hh parallelize/delayline.hh
generator/contextor.o: generator/contextor.hh
generator/description.o: generator/description.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh
generator/description.o: tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh tlib/smartpointer.hh
generator/description.o: generator/uitree.hh generator/Text.hh
generator/klass.o: tlib/smartpointer.hh generator/klass.hh signals/sigtype.hh signals/interval.hh tlib/tlib.hh
generator/klass.o: tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
generator/klass.o: generator/uitree.hh generator/Text.hh signals/signals.hh signals/binop.hh
generator/occurences.o: signals/recursivness.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh
generator/occurences.o: tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh generator/occurences.hh
generator/occurences.o: signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh signals/sigtyperules.hh
generator/sharing.o: generator/compile_vect.hh generator/compile_scal.hh generator/compile.hh signals/signals.hh
generator/sharing.o: tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
generator/sharing.o: signals/binop.hh generator/klass.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh
generator/sharing.o: generator/uitree.hh generator/Text.hh generator/description.hh signals/sigtyperules.hh
generator/sharing.o: generator/occurences.hh tlib/property.hh parallelize/loop.hh signals/sigprint.hh
generator/Text.o: generator/Text.hh tlib/compatibility.hh parser/unistd.h /usr/include/unistd.h
generator/uitree.o: generator/uitree.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
generator/uitree.o: tlib/shlysis.hh
normalize/normalize.o: tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
normalize/normalize.o: signals/signals.hh signals/binop.hh signals/sigprint.hh normalize/simplify.hh
normalize/normalize.o: normalize/normalize.hh signals/sigorderrules.hh
normalize/privatise.o: signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh tlib/compatibility.hh
normalize/privatise.o: parser/unistd.h /usr/include/unistd.h signals/sigprint.hh signals/signals.hh tlib/tlib.hh
normalize/privatise.o: tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
normalize/privatise.o: signals/binop.hh signals/sigtyperules.hh normalize/privatise.hh
normalize/simplify.o: signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh signals/sigtyperules.hh
normalize/simplify.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
normalize/simplify.o: tlib/shlysis.hh signals/binop.hh signals/sigorderrules.hh signals/sigprint.hh
normalize/simplify.o: normalize/simplify.hh extended/xtended.hh generator/klass.hh generator/uitree.hh
normalize/simplify.o: signals/sigvisitor.hh normalize/normalize.hh
parallelize/delayline.o: parallelize/delayline.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh
parallelize/delayline.o: generator/klass.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
parallelize/delayline.o: tlib/list.hh tlib/shlysis.hh generator/uitree.hh generator/Text.hh
parallelize/graphSorting.o: parallelize/graphSorting.hh parallelize/loop.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh
parallelize/graphSorting.o: tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
parallelize/loop.o: parallelize/loop.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
parallelize/loop.o: tlib/shlysis.hh
parser/enrobage.o: parser/enrobage.hh tlib/compatibility.hh parser/unistd.h /usr/include/unistd.h
parser/faustlexer.o: tlib/tree.hh tlib/symbol.hh tlib/node.hh parser/faustparser.hpp parser/unistd.h
parser/faustlexer.o: /usr/include/unistd.h
parser/faustparser.o: tlib/tree.hh tlib/symbol.hh tlib/node.hh extended/xtended.hh tlib/tlib.hh tlib/num.hh
parser/faustparser.o: tlib/list.hh tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh
parser/faustparser.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh signals/signals.hh signals/binop.hh
parser/faustparser.o: boxes/boxes.hh signals/prim2.hh errors/errormsg.hh parser/sourcereader.hh
parser/sourcereader.o: parser/sourcereader.hh boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh
parser/sourcereader.o: tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/signals.hh signals/binop.hh parser/enrobage.hh
parser/sourcereader.o: boxes/ppbox.hh
patternmatcher/patternmatcher.o: tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
patternmatcher/patternmatcher.o: tlib/shlysis.hh boxes/boxes.hh signals/signals.hh signals/binop.hh boxes/ppbox.hh
patternmatcher/patternmatcher.o: evaluate/eval.hh parser/sourcereader.hh patternmatcher/patternmatcher.hh
propagate/propagate.o: propagate/propagate.hh boxes/boxes.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh
propagate/propagate.o: tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/signals.hh signals/binop.hh signals/prim2.hh
propagate/propagate.o: signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh boxes/ppbox.hh extended/xtended.hh
propagate/propagate.o: generator/klass.hh generator/uitree.hh signals/sigvisitor.hh
signals/binop.o: signals/binop.hh tlib/node.hh tlib/symbol.hh
signals/ppsig.o: signals/ppsig.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
signals/ppsig.o: tlib/list.hh tlib/shlysis.hh signals/binop.hh signals/prim2.hh signals/sigtype.hh tlib/smartpointer.hh
signals/ppsig.o: signals/interval.hh extended/xtended.hh generator/klass.hh generator/uitree.hh signals/sigvisitor.hh
signals/ppsig.o: signals/recursivness.hh
signals/prim2.o: signals/prim2.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
signals/prim2.o: tlib/shlysis.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh
signals/recursivness.o: signals/recursivness.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh
signals/recursivness.o: tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh
signals/signals.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
signals/signals.o: tlib/shlysis.hh signals/binop.hh
signals/sigorderrules.o: signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh signals/sigprint.hh
signals/sigorderrules.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
signals/sigorderrules.o: tlib/list.hh tlib/shlysis.hh signals/binop.hh signals/prim2.hh signals/sigorderrules.hh
signals/sigorderrules.o: extended/xtended.hh generator/klass.hh generator/uitree.hh signals/sigvisitor.hh
signals/sigprint.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
signals/sigprint.o: tlib/shlysis.hh signals/binop.hh signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh
signals/sigprint.o: signals/sigtyperules.hh
signals/sigtype.o: signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh
signals/sigtyperules.o: signals/sigtype.hh tlib/smartpointer.hh signals/interval.hh signals/sigprint.hh
signals/sigtyperules.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh
signals/sigtyperules.o: tlib/list.hh tlib/shlysis.hh signals/binop.hh signals/ppsig.hh signals/prim2.hh
signals/sigtyperules.o: signals/sigtyperules.hh extended/xtended.hh generator/klass.hh generator/uitree.hh
signals/sigtyperules.o: signals/sigvisitor.hh
signals/sigvisitor.o: signals/sigvisitor.hh signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh
signals/sigvisitor.o: tlib/num.hh tlib/list.hh tlib/shlysis.hh signals/binop.hh extended/xtended.hh signals/sigtype.hh
signals/sigvisitor.o: tlib/smartpointer.hh signals/interval.hh generator/klass.hh generator/uitree.hh
signals/subsignals.o: signals/signals.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
signals/subsignals.o: tlib/shlysis.hh signals/binop.hh
tlib/list.o: tlib/list.hh tlib/symbol.hh tlib/tree.hh tlib/node.hh tlib/compatibility.hh parser/unistd.h
tlib/list.o: /usr/include/unistd.h
tlib/node.o: tlib/node.hh tlib/symbol.hh
tlib/occurrences.o: tlib/occurrences.hh tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh
tlib/occurrences.o: tlib/shlysis.hh tlib/compatibility.hh parser/unistd.h /usr/include/unistd.h
tlib/recursive-tree.o: tlib/tlib.hh tlib/symbol.hh tlib/node.hh tlib/tree.hh tlib/num.hh tlib/list.hh tlib/shlysis.hh
tlib/shlysis.o: tlib/shlysis.hh tlib/list.hh tlib/symbol.hh tlib/tree.hh tlib/node.hh tlib/compatibility.hh
tlib/shlysis.o: parser/unistd.h /usr/include/unistd.h
tlib/symbol.o: tlib/symbol.hh tlib/compatibility.hh parser/unistd.h /usr/include/unistd.h
tlib/tree.o: tlib/tree.hh tlib/symbol.hh tlib/node.hh
draw/device/PSDev.o: draw/device/PSDev.h draw/device/device.h tlib/compatibility.hh parser/unistd.h
draw/device/PSDev.o: /usr/include/unistd.h
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
