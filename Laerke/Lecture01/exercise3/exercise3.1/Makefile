all:	exe

exe:	main.o part1.o part2.o
		g++ -o exe main.o part1.o part2.o
	
main.o:	main.cpp part1.h part2.h
		g++ -c main.cpp
	
part1.o:part1.cpp
		g++ -c part1.cpp
			
part2.o:part2.cpp
		g++ -c part2.cpp

clean:		
		rm *.o exe
		
help:	
		@echo "\t exe:\n\t excutable file\n"
		@echo "\t main.o:\n\t main.o file, who calls part1 and part2\n"
		@echo "\t part1.o:\n\t part1.o file, with function part1()\n"
		@echo "\t part2.o:\n\t part2.o file, with function part2()\n"
		@echo "\t clean:\n\t Remove alle the object file and the executable\n"
		@echo "\t all:\n\t run the program\n"
		
