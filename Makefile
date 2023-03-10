# Compiler flags
CXXFLAGS = -Wall -O3 -I./include -I./src

# Source files
PIXEL_SOURCES = pixel.cc
TEST_SOURCES = test.cc
SOURCE_FILES = src/statemachine.cc src/color.cc src/state.cc src/wave.cc
SOURCE_OBJECTS = $(SOURCE_FILES:.cc=.o)

# build the spotify-json library
SPOTIFY_OBJECTS = src/spotify.o
SPOTIFY_SOURCES = src/spotify.cc
SPOTIFY_LIB = spotify-json


RGB_LIB_DISTRIBUTION=matrix
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread


# Object files
TEST_OBJECTS = test.o
PIXEL_OBJECTS = pixel.o
TEST_WAVE_OBJECTS = testwave.o
SPOTIFY_OBJECTS = testspotify.o


# Executables
PIXEL_BINARIES = pixel
TEST_BINARIES = test


RGB_INCDIR=matrix/include

LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR)	

spotify : $(SPOTIFY_OBJECTS) $(SPOTIFY_SOURCES)
	$(CXX)  $(CXXFLAGS) $(SPOTIFY_OBJECTS) -o $@ $(LDFLAGS)


test_wave : src/wave.o src/state.o $(TEST_WAVE_OBJECTS) $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) -I$(RGB_INCDIR) $(TEST_WAVE_OBJECTS) src/wave.o src/state.o -o $@ $(LDFLAGS)

test_wave.o : test_wave.cc

test : $(TEST_OBJECTS) $(SOURCE_OBJECTS) 
	$(CXX) $(CXXFLAGS) $(TEST_OBJECTS) $(SOURCE_OBJECTS) -o $@

test.o : test.cc 


pixel : $(PIXEL_OBJECTS) $(RGB_LIBRARY) $(SOURCE_OBJECTS)
	$(CXX)  $(CXXFLAGS) $(PIXEL_OBJECTS) $(SOURCE_OBJECTS) -o $@ $(LDFLAGS)
	

pixel.o : pixel.cc

%.o : %.cc
	$(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<

FORCE:
.PHONY: FORCE

clean :
	rm -f $(TEST_OBJECTS) $(TEST_BINARIES) $(PIXEL_BINARIES) $(SOURCE_OBJECTS) $(PIXEL_OBJECTS) $(TEST_WAVE_OBJECTS)
	$(MAKE) -C $(RGB_LIBDIR) clean
	