BUILD_DIR = host

hello: 	 ${BUILD_DIR}/hello.o
	  g++ -o ${BUILD_DIR}/hello ${BUILD_DIR}/hello.o
	  
${BUILD_DIR}/hello.o: ${BUILD_DIR} hello.cpp
	  g++ -c -o ${BUILD_DIR}/hello.o hello.cpp
	  
clean:	 
	  rm -r ${BUILD_DIR}

help:
	  @echo "\t hello:\n\t Invoke compiler g++ to create executable hello from object file hello.o\n"
	  @echo "\t hello.o:\n\t Invoke compiler g++ to create an object file hello.o from source file hello.cpp\n"
	  @echo "\t clean:\n\t removees all the object files as well as the executable\n"
	  
${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}

	