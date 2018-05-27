CC=clang
CXX=clang++

INCDIR=include
SRCDIR=src
BINDIR=bin
OBJDIR=obj

BINARY=swaps
OBJECTS=$(patsubst %.o,$(OBJDIR)/%.o,\
					arrangement.o \
					helpers.o \
					main.o \
					permutahedron.o \
					swap.o \
					word.o)

all: $(BINARY)

# Reassign OBJECTS to include the object path
CXXFLAGS+=-I$(INCDIR) -Wall -g -O3 --std=c++11

$(BINARY) : $(OBJECTS) $(RGB_LIBRARY)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$@ $^ $(LDFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -f $(BINDIR)/* $(OBJDIR)/*
