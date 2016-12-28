SOURCES=hello.cpp
OBJECTS=${SOURCES:.cpp=.o}
EXECUTABLE=main
CXX=g++
LDFLAGS=-lncurses

all: ${OBJECTS}
	  @${CXX} -o ${EXECUTABLE} ${OBJECTS} $(LDFLAGS)

%.o: %.cpp
	@${CXX} -c -o $@ $^

clean: 
	@rm -f ${EXECUTABLE} ${OBJECTS}

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
