EXE=Hello
CXX=g++

all: hello.o
	$(CXX) -o $(EXE) hello.o

hello.o: hello.cpp
	$(CXX) -c hello.cpp

clean: 
	rm Hello hello.o

help: 
	@echo "Available targets:	Action:"
	@echo "all			Builds target"
	@echo "hello.o			Remake o file"
	@echo "clean			delete o and target"
