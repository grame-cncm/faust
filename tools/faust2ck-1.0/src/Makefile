
faust2ck: faust2ck.o

faust2ck.o: chuck_faust.template.h

chuck_faust.template.h: chuck_faust.template
	sed  -e 's/\\/\\\\/g' -e 's/"/\\"/g' -e 's/\(.*\)/"\1",/' $< >$@
