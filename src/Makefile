OBJECTS=state.o color.o
BINARIES=state color

HEADERSDIR=../include

CXXFLAGS=-I$(HEADERSDIR)

all : state

state : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

clean :
	rm -f $(OBJECTS) $(BINARIES)