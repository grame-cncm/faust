
.PHONY: README.md

ROOT = ../..

readme:
	make README.md > README.md
	cp README.md $(ROOT)/compiler

README.md:
	@cat man-header.txt
	@$(ROOT)/build/bin/faust -h | tail -n +6 \
			 | sed -e 's/\(-[a-zA-Z][a-zA-Z0-9]*\)/**\1**/' \
			 | sed -e 's/\(--[a-zA-Z][a-zA-Z0-9-]*\)/**\1**/' \
			 | sed -e 's/</\\</g' \
			 | sed '/-----*/ G' \
			 | sed '/\.$$/ G' 
	@cat man-footer.txt

man:
	make faust.1

faust.1 : man1 readme
	pandoc --standalone --to man README.md -o faust.1
	sed -i '' 's/\\\[en]/\\-\\-/g' faust.1
	mv -f faust.1 man1

man1:
	mkdir man1
