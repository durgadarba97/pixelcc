OBJECTS=statemachine.o color.o wave.o
BINARIES=statemachine

HEADERSDIR=../include 

CXXFLAGS=-I$(HEADERSDIR)

all : statemachine

statemachine : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

clean :
	rm -f $(OBJECTS) $(BINARIES)