
# make sure you set the proper prefixes where the Q interpreter and Pd live
#prefix=/usr
prefix=/usr/local
#pdprefix=/usr
pdprefix=/usr/local

bindir=$(prefix)/bin
libdir=$(prefix)/lib/q
datadir=$(prefix)/share/q
appdir=$(datadir)/apps/faust2pd
pddatadir=$(pdprefix)/lib/pd/extra

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
	test -d $(DESTDIR)$(appdir) || mkdir -p $(DESTDIR)$(appdir)
	test -d $(DESTDIR)$(datadir)/lib || mkdir -p $(DESTDIR)$(datadir)/lib
	test -d $(DESTDIR)$(datadir)/etc || mkdir -p $(DESTDIR)$(datadir)/etc
	cp README $(DESTDIR)$(datadir)/etc/README-Faust2Pd
	cp faust2pd/faustxml.q $(DESTDIR)$(datadir)/lib/faustxml.q
	sed -e 's?#!/usr/bin/q?#!$(bindir)/q?g' < faust2pd/faust2pd.q > $(DESTDIR)$(appdir)/faust2pd.q
	chmod a+x $(DESTDIR)$(appdir)/faust2pd.q
	test -d $(DESTDIR)$(bindir) || mkdir -p $(DESTDIR)$(bindir)
	ln -sf $(appdir)/faust2pd.q $(DESTDIR)$(bindir)/faust2pd
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	@echo "Please run make install-pd to also install the auxiliary Faust abstractions"
	@echo "in $(DESTDIR)$(pddatadir)."
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

# install the auxiliary Faust abstractions (faust-*.pd)
install-pd:
	test -d $(DESTDIR)$(pddatadir) || mkdir -p $(DESTDIR)$(pddatadir)
	cp faust2pd/faust-*.pd $(DESTDIR)$(pddatadir)

#uninstall
uninstall:
	rm -f $(DESTDIR)$(bindir)/faust2pd
	rm -rf $(DESTDIR)$(appdir)
	rm -f $(DESTDIR)$(datadir)/etc/README-Faust2Pd
	rm -f $(DESTDIR)$(datadir)/lib/faustxml.q
	rm -f $(DESTDIR)$(pddatadir)/faust-*.pd
