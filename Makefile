# Compiler flags
CXXFLAGS = -Wall -O3 -I./src -Ijson/include -std=c++20 -g

# Source files
PIXEL_SOURCES = pixel.cc

# 1. add the source file here
SOURCE_FILES = src/color.cc src/state.cc src/wave.cc src/conway.cc src/lorenz.cc
SOURCE_OBJECTS = $(SOURCE_FILES:.cc=.o)

# build the spotify-json library
SPOTIFY_OBJECTS = src/spotify.o
SPOTIFY_SOURCES = src/spotify.cc


RGB_LIB_DISTRIBUTION=matrix
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread


# Object files
# 2. add the object file here
TEST_OBJECTS = test.o
PIXEL_OBJECTS = pixel.o
TEST_WAVE_OBJECTS = tests/testwave.o
SPOTIFY_OBJECTS = tests/testspotify.o
CONWAY_OBJECTS = tests/testconway.o
LORENZ_OBJECTS = tests/testlorenz.o


# Executables
PIXEL_BINARIES = pixel
TEST_BINARIES = test
SPOTIFY_BINARIES = spotify

$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR)	

lorenz : src/lorenz.o $(LORENZ_OBJECTS) $(SOURCE_OBJECTS) $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) -I$(RGB_INCDIR) $(LORENZ_OBJECTS) $(SOURCE_OBJECTS) -o $@  $(LDFLAGS)

conway : src/conway.o $(CONWAY_OBJECTS) $(SOURCE_OBJECTS) $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) $(CONWAY_OBJECTS) $(SOURCE_OBJECTS) -o $@ $(LDFLAGS)

spotify : $(SPOTIFY_OBJECTS) $(SPOTIFY_SOURCES)
	$(CXX)  $(CXXFLAGS) $(SPOTIFY_OBJECTS) -o $@ -lcurl


wave : src/wave.o src/state.o $(TEST_WAVE_OBJECTS) $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) -I$(RGB_INCDIR) $(TEST_WAVE_OBJECTS) src/wave.o src/state.o -o $@ $(LDFLAGS)

wave.o : test_wave.cc

test : $(TEST_OBJECTS) $(SOURCE_OBJECTS) 
	$(CXX) $(CXXFLAGS) $(TEST_OBJECTS) $(SOURCE_OBJECTS) -o $@



pixel : $(PIXEL_OBJECTS) $(RGB_LIBRARY) $(SOURCE_OBJECTS)
	$(CXX)  $(CXXFLAGS) $(PIXEL_OBJECTS) $(SOURCE_OBJECTS) -o $@ $(LDFLAGS)
	

pixel.o : pixel.cc

%.o : %.cc
	$(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<

FORCE:
.PHONY: FORCE

clean :
	rm -f $(TEST_OBJECTS) $(TEST_BINARIES) $(PIXEL_BINARIES) $(SOURCE_OBJECTS) $(PIXEL_OBJECTS) $(TEST_WAVE_OBJECTS) $(SPOTIFY_OBJECTS) $(SPOTIFY_BINARIES)
	$(MAKE) -C $(RGB_LIBDIR) clean