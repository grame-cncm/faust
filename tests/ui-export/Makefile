CXX ?= c++
CXXFLAGS ?= -std=c++17 -I../../architecture

GEN = gen_ui
SRC = generate_ui.cpp
SVG_ALL = layoutui-simple.svg layoutui-medium.svg layoutui-vertical.svg layoutui-horizontal.svg layoutui-tabs.svg layoutui-complex.svg
HTML_ALL = layoutui-simple.html layoutui-medium.html layoutui-vertical.html layoutui-horizontal.html layoutui-tabs.html layoutui-complex.html

.PHONY: all svg check clean svg-simple svg-medium svg-complex

all: $(GEN)

$(GEN): $(SRC) \
	../../architecture/faust/gui/SVGExport.h \
	../../architecture/faust/gui/HTMLExport.h \
	../../architecture/faust/gui/MetaDataUI.h \
	../../architecture/faust/gui/LayoutUI.h
	$(CXX) $(CXXFLAGS) $(SRC) -o $(GEN)

svg: $(GEN)
	./$(GEN)

check: svg
	python3 check_svg.py
	python3 check_html.py

clean:
	rm -f $(GEN) $(SVG_ALL) $(HTML_ALL)
