IDIR =../inc
CC=g++
CFLAGS=-I$(IDIR) -stdlib=libc++ -std=c++11 -g -O0

ODIR=../bin
TDIR=../bin/tmp
LDIR =../bin

LIBS=-lm

_DEPS := $(shell find $(IDIR) -name '*.h')
DEPS := $(patsubst %,$(IDIR)/%,$(_DEPS))

CPP_FILES = $(wildcard ./*.cpp)
OBJ_FILES = $(addprefix $(TDIR)/,$(notdir $(CPP_FILES:.cpp=.o)))

$(TDIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ_FILES)
	$(CC) -o $(ODIR)/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(TDIR)/*.o *~ $(IDIR)/*~ 
