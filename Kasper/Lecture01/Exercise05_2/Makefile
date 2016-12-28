SOURCES=main.cpp part1.cpp
OBJECTS=${SOURCES:.cpp=.o}
LIB_SOURCES = libs/part2.cpp
LIB_OBJECTS=${LIB_SOURCES:.cpp=.o}
LIB=libs/libparts.a
EXECUTABLE=main
CXX=g++
LDFLAGS=-L./libs/ -lparts

all: static

static: ${OBJECTS} ${LIB}
	@${CXX} -static -o  ${EXECUTABLE} ${OBJECTS} ${LDFLAGS}

%.o: %.cpp
	@${CXX} -c -o $@ $^

clean: 
	@rm -f ${EXECUTABLE} ${OBJECTS} ${LIB}

help:
	@echo "Targets:"
	@echo "  all"
	@echo "  clean"
	@echo "  help"
	@echo ""
	@echo "Vars:"
	@echo "  CXX"
	@echo "  EXECUTABLE"
	@echo "" 

libs/%.o: libs/%.cpp
	@${CXX} -c -o $@ $^

${LIB}: ${LIB_OBJECTS}
	@ar rcs $@ $^
	@rm $^

