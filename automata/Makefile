CXX := g++
CXX_ARGS := -std=c++17
TARGETS := even-ab end-oh-one-one general-balanced even-oh-one

all: $(TARGETS)

sync: all
	- scp -r . patty:fa

%: %.cc FALexer.hh
	$(CXX) $(CXX_ARGS) -g -o $@ $*.cc

%.cc: %.ll FALexer.hh
	flex -o $@ $*.ll

clean:
	-rm -rf $(TARGETS)
	-rm -rf *.dSYM
	-rm -rf *.cc

.PHONY: clean sync
