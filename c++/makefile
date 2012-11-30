CPP=g++-4.2
INC=-Iinclude

SURF_HFILES=include/point.h include/edge.h include/tri.h include/poly.h include/cube.h
SURF_OBJFILES=build/point.o build/edge.o build/tri.o build/poly.o build/cube.o

surf : lib/libsurf.a main.cpp
	${CPP} main.cpp -o surf ${INC} -Llib -lsurf

clean :
	rm -f lib/libsurf.a;\
	rm -f ./surf;

lib/libsurf.a : ${SURF_OBJFILES}
	rm -f lib/libsurf.a;\
	ar r lib/libsurf.a ${SURF_OBJFILES};

build/point.o : ${SURF_HFILES} src/point.cpp
	${CPP} ${INC} -c src/point.cpp -o build/point.o
	
build/edge.o : ${SURF_HFILES} src/edge.cpp
	${CPP} ${INC} -c src/edge.cpp -o build/edge.o
	
build/tri.o : ${SURF_HFILES} src/tri.cpp
	${CPP} ${INC} -c src/tri.cpp -o build/tri.o
	
build/poly.o : ${SURF_HFILES} src/poly.cpp
	${CPP} ${INC} -c src/poly.cpp -o build/poly.o
	
build/cube.o : ${SURF_HFILES} src/cube.cpp
	${CPP} ${INC} -c src/cube.cpp -o build/cube.o
	
include/point.h : src/point.h
	cp -f src/point.h include/
	
include/edge.h : src/edge.h
	cp -f src/edge.h include/
	
include/tri.h : src/tri.h
	cp -f src/tri.h include/
	
include/poly.h : src/poly.h
	cp -f src/poly.h include/
	
include/cube.h : src/cube.h
	cp -f src/cube.h include/