# CXXFLAGS=-O3
# OBJECTS=pixel.o statemachine.o color.o state.o wave.o
# BINARIES=pixel

# PIXEL_INCDIR=./include
# PIXEL_SRC=./src

# TEST_OBJECTS=test.o src/statemachine.o color.o state.o wave.o
# TEST_BINARIES=test

# RGB_INCDIR=matrix/include
# RGB_LIBDIR=matrix/lib
# RGB_LIBRARY_NAME=rgbmatrix
# RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a



# LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

# all : pixel

# pixel : $(OBJECTS) $(RGB_LIBRARY)
# 	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

# $(RGB_LIBRARY): FORCE
# 	$(MAKE) -C $(RGB_LIBDIR)

# test : $(TEST_OBJECTS) 
# 	$(CXX) $(CXXFLAGS) $(TEST_OBJECTS) -o

# pixel.o : pixel.cc

# test.o : test.cc

# %.o : %.cc
# 	$(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<

# clean:
# 	rm -f $(TEST_OBJECTS) $(TEST_BINARIES) $(OBJECTS) $(BINARIES) 
# 	$(MAKE) -C $(RGB_LIBDIR)


# FORCE:
# .PHONY: FORCE




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

# rewriting the makefile to this

# import statemachine header from include folder
#  import all source files from src folder
#  compile all source files
#  link all object files to test binary

# import matrix header from matrix/include folder
#  import matrix library from matrix/lib folder
# compile rule pixel.o : pixel.cc


# Compiler flags
CXXFLAGS = -Wall -I./include -O3

# Source files
PIXEL_SOURCES = pixel.cc
TEST_SOURCES = test.cc
SOURCE_FILES = src/statemachine.cc src/color.cc src/state.cc src/wave.cc
SOURCE_OBJECTS = $(SOURCE_FILES:.cc=.o)

RGB_LIB_DISTRIBUTION=matrix
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread


# Object files
TEST_OBJECTS = test.o
# PIXEL_OBJECTS = $(PIXEL_SOURCES:.cc=.o)
# TEST_OBJECTS = $(TEST_SOURCES:.cc=.o)
# OBJECT_FILES = $(SOURCE_FILES:.cc=.o)

# Executables
PIXEL_BINARIES = pixel
TEST_BINARIES = test

LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR)

testwave : testwave.o src/wave.o src/state.o $(RGB_LIBRARY)
	$(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) testwave.o src/wave.o src/state.o -o $@ $(LDFLAGS)

testwave.o : testwave.cc

test : $(TEST_OBJECTS) $(SOURCE_OBJECTS) 
	$(CXX) $(CXXFLAGS) $(TEST_OBJECTS) $(SOURCE_OBJECTS) -o $@

test.o : test.cc 

pixel : $(SOURCE_OBJECTS) pixel.o $(RGB_LIBRARY)
	$(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) $(SOURCE_OBJECTS) -o $@ $(LDFLAGS)


clean :
	rm -f $(TEST_OBJECTS) $(TEST_BINARIES) $(PIXEL_BINARIES) $(SOURCE_OBJECTS)
	$(MAKE) -C $(RGB_LIBDIR) clean
	