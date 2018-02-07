
# Package name and version number:
dist = faust2pd-$(version)
version = 2.12

# Default installation prefix:
prefix = /usr/local

# Try to guess the Pd installation prefix:
pdprefix = $(patsubst %/bin/pd,%,$(shell which pd 2>/dev/null))
ifeq ($(strip $(pdprefix)),)
# Fall back to /usr/local.
pdprefix = /usr/local
endif

bindir = $(prefix)/bin
# where to install the Pd stuff
libdir = $(pdprefix)/lib
datadir = $(libdir)/pd/extra

# Try to guess the host system type and do platform-specific setup.
host = $(shell ./config.guess)
ifneq "$(findstring -mingw,$(host))" ""
# Windows
EXE = .exe
endif

DESTDIR=

DISTFILES = Makefile COPYING ChangeLog README config.guess *.pure *.pd examples/README debian/* examples/*/Makefile examples/*/*.cpp examples/*/*.dsp examples/*/*.syn examples/*/*.pd examples/*/*.pure examples/*/*.xml pd/*.h
SEDFILES = README

.PHONY: all examples clean distclean realclean install uninstall

all: faust2pd$(EXE)

examples: faust2pd$(EXE)
	for x in basic faust synth seqdemo; do $(MAKE) -C examples/$$x all; done

clean:
	rm -f faust2pd$(EXE)
	for x in basic faust synth seqdemo; do $(MAKE) -C examples/$$x clean; done

distclean:
	rm -f faust2pd$(EXE)
	for x in basic faust synth seqdemo; do $(MAKE) -C examples/$$x distclean; done

realclean:
	rm -f faust2pd$(EXE)
	for x in basic faust synth seqdemo; do $(MAKE) -C examples/$$x realclean; done

# as of pure-0.21, we can compile the script to an executable
faust2pd$(EXE): faust2pd.pure faustxml.pure
	sed -e 's?@version@?$(version)?' < $< > xx$<
	pure $(PUREC_FLAGS) -I. -c xx$< -o $@
	rm -f xx$<

# install faust2pd
install:
	test -d $(DESTDIR)$(bindir) || mkdir -p $(DESTDIR)$(bindir)
	cp faust2pd$(EXE) $(DESTDIR)$(bindir)
	strip $(DESTDIR)$(bindir)/faust2pd$(EXE)
ifeq "$(findstring -mingw,$(host))" ""
	chmod a+x $(DESTDIR)$(bindir)/faust2pd$(EXE)
endif
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	@echo "Optionally, you can also run make install-pd to install the auxiliary Faust"
	@echo "abstractions in $(DESTDIR)$(datadir)."
	@echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

# install the auxiliary Faust abstractions (faust-*.pd)
install-pd:
	test -d $(DESTDIR)$(datadir) || mkdir -p $(DESTDIR)$(datadir)
	cp faust-*.pd $(DESTDIR)$(datadir)

#uninstall
uninstall:
	rm -rf $(DESTDIR)$(bindir)/faust2pd$(EXE)
	rm -f $(DESTDIR)$(datadir)/faust-*.pd

.PHONY: dist distcheck

# roll distribution tarball

date = $(shell date "+%B %-d, %Y")
datesubst = sed -e "s?@version@?$(version)?g" -e "s?|today|?$(date)?g" < $(1) > $(2)

dist:
	rm -rf $(dist)
	mkdir $(dist) && mkdir $(dist)/debian && mkdir $(dist)/pd && mkdir $(dist)/examples
	for x in basic faust seqdemo synth; do mkdir $(dist)/examples/$$x; done
	for x in $(DISTFILES); do ln -sf $$PWD/$$x $(dist)/$$x; done
	for x in $(SEDFILES); do rm -f $(dist)/$$x; $(call datesubst,$$PWD/$$x,$(dist)/$$x); done
	rm -f $(dist).tar.gz
	tar cfzh $(dist).tar.gz $(dist)
	rm -rf $(dist)

distcheck: dist
	tar xfz $(dist).tar.gz
	cd $(dist) && $(MAKE) all examples && $(MAKE) install install-pd DESTDIR=./BUILD
	rm -rf $(dist)

# Debian packaging

debsrc = $(shell echo $(dist) | sed -e 's/-$(version)/_$(version)/').orig.tar.gz

deb: $(debsrc) dist
	tar xfz $(dist).tar.gz
	cd $(dist) && debuild $(DEBUILD_FLAGS)
	rm -rf $(dist)

$(debsrc):
	wget -nv https://bitbucket.org/purelang/pure-lang/downloads/$(dist).tar.gz -O $@

# Generate the documentation.

sources = faustxml.pure

faust2pd.txt: README $(sources)
	pure-doc $(sources) | cat README - > $@
