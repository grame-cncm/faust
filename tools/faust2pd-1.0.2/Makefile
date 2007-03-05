
# make sure you set the proper prefix where the Q interpreter lives
#prefix=/usr
prefix=/usr/local

bindir=$(prefix)/bin
libdir=$(prefix)/lib/q
datadir=$(prefix)/share/q
pddatadir=/usr/local/lib/pd/extra
#pddatadir=$(prefix)/lib/pd/extra

DESTDIR=

all:
	for x in basic faust synth seqdemo; do make -C examples/$$x all; done

clean:
	for x in basic faust synth seqdemo; do make -C examples/$$x clean; done

distclean:
	for x in basic faust synth seqdemo; do make -C examples/$$x distclean; done

realclean:
	for x in basic faust synth seqdemo; do make -C examples/$$x realclean; done

# install the faust2pd script and accompanying files
install:
	cp faust2pd/faustxml.q $(DESTDIR)$(datadir)/lib/faustxml.q
	sed -e 's?#!/usr/bin/q?#!$(bindir)/q?g' < faust2pd/faust2pd.q > $(DESTDIR)$(datadir)/lib/faust2pd.q
	chmod a+x $(DESTDIR)$(datadir)/lib/faust2pd.q
	ln -sf $(datadir)/lib/faust2pd.q $(DESTDIR)$(bindir)/faust2pd
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	@echo "Please run make install-pd to also install the auxiliary Faust abstractions"
	@echo "in $(DESTDIR)$(pddatadir)."
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

# install the auxiliary Faust abstractions (faust-*.pd)
install-pd:
	cp faust2pd/faust-*.pd $(DESTDIR)$(pddatadir)

#uninstall
uninstall:
	rm -f $(DESTDIR)$(datadir)/lib/faustxml.q $(DESTDIR)$(datadir)/lib/faust2pd.q
	rm -Rf $(DESTDIR)$(pddatadir)/faust-*.pd
