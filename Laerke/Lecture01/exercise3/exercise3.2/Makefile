SOURCES=main.cpp part1.cpp part2.cpp
OBJECTS=${SOURCES:.cpp=.o}
EXECUTABLE=exe
CXX=g++

%.o: %.cpp
	${CXX} -c -o $@ $^
	
${EXECUTABLE}: ${OBJECTS}
	${CXX} -o $@ $^