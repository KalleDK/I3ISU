BIN=main
CXX=g++

all:    ${BIN}

${BIN}:    main.o part1.o part2.o
	${CXX} -o ${BIN} main.o part1.o part2.o

main.o:    main.cpp part1.h part2.h
	${CXX} -c main.cpp

part1.o: part1.cpp
	${CXX} -c part1.cpp

part2.o: part2.cpp
	${CXX} -c part2.cpp

clean:        
	rm *.o ${BIN}

help:    
	@echo "\t ${BIN}:\n\t excutable file\n" 
	@echo "\t main.o:\n\t main.o file, who calls part1 and part2\n" 
	@echo "\t part1.o:\n\t part1.o file, with function part1()\n" 
	@echo "\t part2.o:\n\t part2.o file, with function part2()\n" 
	@echo "\t clean:\n\t Remove alle the object file and the executable\n" 
	@echo "\t all:\n\t builds the program\n"
