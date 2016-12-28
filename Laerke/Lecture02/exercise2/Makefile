hello: 	 hello.o
	  g++ -o hello hello.o
	  
hello.o: hello.cpp
	  g++ -c hello.cpp
	  
clean:	 
	  rm *.o hello

help:
	  @echo "\t hello:\n\t Invoke compiler g++ to create executable hello from object file hello.o\n"
	  @echo "\t hello.o:\n\t Invoke compiler g++ to create an object file hello.o from source file hello.cpp\n"
	  @echo "\t clean:\n\t removees all the object files as well as the executable\n"