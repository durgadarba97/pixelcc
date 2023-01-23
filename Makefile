CXXFLAGS=-O3
OBJECTS=pixel.o 
BINARIES=pixel

PIXEL_LIBDIR=../lib

RGB_INCDIR=matrix/include
RGB_LIBDIR=matrix/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a



LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

all : pixel

pixel : $(OBJECTS) $(RGB_LIBRARY) $(PIXEL_LIBDIR)
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