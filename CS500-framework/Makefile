
########################################################################
# Makefile for Linux
########################################################################

CXX = g++

ifneq (,$(wildcard libs))
    LIBDIR := libs
else
    ifneq (,$(wildcard ../libs))
        LIBDIR := ../libs
    else
        ifneq (,$(wildcard ../../libs))
            LIBDIR := ../../libs
        else
            LIBDIR := ../../../libs
        endif
    endif
endif

OPTIMIZE = -g -O4

BROKENCXXFLAGS = $(OPTIMIZE) -std=c++11 -I$(LIBDIR)/glm -I$(LIBDIR) -I/usr/include -I$(LIBDIR)/assimp/include -Wnarrowing -I.  -fopenmp -msse3 -DEIGEN_NO_DEBUG -Wno-deprecated-declarations

CXXFLAGS = $(OPTIMIZE) -std=c++11 -I. -I$(LIBDIR)/freeglut -I$(LIBDIR)/glm -I$(LIBDIR) -I/usr/include  -I$(LIBDIR)/assimp/include -Wnarrowing -I.  -fopenmp -msse3 -DEIGEN_NO_DEBUG -Wno-deprecated-declarations

LIBS = -L$(LIBDIR) -L/usr/lib -L/usr/local/lib -lassimp -lglbinding -lglut -lX11 -lGLU -lGL


target = raytrace.exe

headers =geom.h raytrace.h  realtime.h rgbe.h
src = geom.cpp main.cpp raytrace.cpp readAssimpFile.cpp realtime.cpp rgbe.cpp
extras = raytrace.vcxproj Makefile realtime.vert realtime.frag 

scenes = testscene.scn letterX.ply letterY.ply jeep1.3ds ~/assets/mesh/bunny.ply dwarf.x

pkgFiles = $(src) $(headers) $(extras) $(scenes)
pkgName = CS500-framework

objects = $(patsubst %.cpp,%.o,$(src))


$(target): $(objects)
	g++  $(CXXFLAGS) -o $@  $(objects) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(target)
	#python3 driver.py
	LD_LIBRARY_PATH="$(LIBDIR); $(LD_LIBRARY_PATH)" ./raytrace.exe testscene.scn

zip:
	rm -rf ../$(pkgName) ../$(pkgName).zip
	mkdir ../$(pkgName)
	cp -r $(pkgFiles) ../$(pkgName)
	cp -r ../libs ../$(pkgName)
	rm -rf ../$(pkgName)/libs/.hg
	cd ..;  zip -r $(pkgName).zip $(pkgName); rm -rf $(pkgName)

pyzip: $(pyFiles)
	rm -rf ../$(pkgName) ../$(pkgName)-py.zip
	mkdir ../$(pkgName)
	cp -r $(pyFiles) ../$(pkgName)
	rm -f `find ../$(pkgName) -name '*.pyc'`
	cd ..;  zip -r $(pkgName)-py.zip $(pkgName); rm -rf $(pkgName)

clean:
	rm -rf *.suo *.sdf *.orig Release Debug ipch *.o *~ raytrace dependencies *13*scn  *13*ppm 

dependencies: 
	g++ -MM $(CXXFLAGS)  $(src) > dependencies

include dependencies
