CXXFLAGS=-O3
OBJECTS=pixel.o 
BINARIES=pixel

PIXEL_INCDIR=./include
PIXEL_SRC=./src

TEST_OBJECTS=test.o
TEST_BINARIES=test

RGB_INCDIR=matrix/include
RGB_LIBDIR=matrix/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a



LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

all : pixel

test : $(TEST_OBJECTS) $(PIXEL_LIBDIR)
	$(CXX) $(CXXFLAGS) $(TEST_OBJECTS)

pixel : $(OBJECTS) $(PIXEL_LIBDIR) $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

$(RGB_LIBRARY): FORCE
	$(MAKE) -C $(RGB_LIBDIR)

pixel.o : pixel.cc

%.o : %.cc
	$(CXX) -I$(RGB_INCDIR)	 $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(BINARIES)
	$(MAKE) -C $(RGB_LIBDIR) $(PIXEL_LIBDIR) clean


FORCE:
.PHONY: FORCE




# OBJECTS=pixel.o statemachine.o color.o state.o wave.o
# BINARIES=pixel

# PIXEL_INCDIR= ./include
# CXXFLAGS=-I$(PIXEL_INCDIR) -I./src

# all : pixel

# pixel : $(OBJECTS)
# 	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

# %.o: %.cc
# 	$(CXX) $(CXXFLAGS) -c $<

# clean :
# 	rm -f $(OBJECTS) $(BINARIES)