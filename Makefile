# Compiler flags
CXXFLAGS = -Wall -O3 -I./src -Ijson/include -I/usr/include/GraphicsMagick -std=c++20 -g -I/usr/include/ImageMagick-6 -Imatrix/include
LDLIBS = -lcurl -lrt -lm -lpthread -lGraphicsMagick++ -lGraphicsMagick

# Source files
PIXEL_SOURCES = pixel.cc

# 1. add the source file here
SOURCE_FILES = src/wave.cc src/conway.cc src/lorenz.cc
SOURCE_OBJECTS = $(SOURCE_FILES:.cc=.o)

RGB_LIB_DISTRIBUTION=matrix
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

MAGICK_CXXFLAGS?=$(shell GraphicsMagick++-config --cppflags --cxxflags)
MAGICK_LDFLAGS?=$(shell GraphicsMagick++-config --ldflags --libs)

TEST_SOURCES = tests/testwave.cc tests/testconway.cc tests/testlorenz.cc
TEST_OBJECTS2 = $(TEST_SOURCES:.cc=.o)


# Object files
# 2. add the object file here
TEST_OBJECTS = tests/testwave.o tests/testconway.o tests/testlorenz.o
PIXEL_OBJECTS = pixel.o
TEST_WAVE_OBJECTS = tests/testwave.o
CONWAY_OBJECTS = tests/testconway.o
LORENZ_OBJECTS = tests/testlorenz.o


# Executables
PIXEL_BINARIES = pixel
TEST_BINARIES = test

$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR)	

spotify: src/spotify.o tests/testspotify.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) -I$(RGB_INCDIR) src/spotify.o tests/testspotify.o -o $@ $(LDFLAGS) $(LDLIBS)

src/spotify.o: src/spotify.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<


boids : src/boids.o tests/testboids.o 
	$(CXX) $(CXXFLAGS) -I src/boids tests/testboids.o -o $@ $<

lorenz : $(TEST_OBJECTS2) $(SOURCE_OBJECTS) $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) -I$(RGB_INCDIR) $(TEST_OBJECTS2) $(SOURCE_OBJECTS) -o $@ $(LDFLAGS)

conway : src/conway.o tests/testconway.o $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) tests/testconway.o -o $@ $(LDFLAGS)

wave : $(TEST_OBJECTS2) $(SOURCE_OBJECTS) $(RGB_LIBRARY)
	$(CXX) $(CXXFLAGS) -I$(RGB_INCDIR) $(TEST_OBJECTS2) $(SOURCE_OBJECTS) -o $@ $(LDFLAGS)

wave.o : test_wave.cc

test : $(TEST_OBJECTS) $(SOURCE_OBJECTS) 
	$(CXX) $(CXXFLAGS) $(TEST_OBJECTS) $(SOURCE_OBJECTS) -o $@

pixel : $(PIXEL_OBJECTS) $(RGB_LIBRARY) $(SOURCE_OBJECTS)
	$(CXX)  $(CXXFLAGS) $(PIXEL_OBJECTS) $(SOURCE_OBJECTS) src/spotify.o -o $@ -lcurl $(LDFLAGS) $(MAGICK_LDFLAGS)
	

pixel.o : pixel.cc

%.o : %.cc
	$(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<

FORCE:
.PHONY: FORCE

clean :
	rm -f $(TEST_OBJECTS) $(TEST_BINARIES) $(PIXEL_BINARIES) $(SOURCE_OBJECTS) $(PIXEL_OBJECTS) $(TEST_WAVE_OBJECTS) $(SPOTIFY_OBJECTS) $(SPOTIFY_BINARIES)
	$(MAKE) -C $(RGB_LIBDIR) clean