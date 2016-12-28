ARCH=host
BUILD_DIR=${ARCH}
SOURCES=ex3.cpp
OBJECTS=$(addprefix ${BUILD_DIR}/, ${SOURCES:.cpp=.o})
EXECUTABLE=main
CXXFLAGS = -lpthread
ifeq (${ARCH},target)
	CXX=arm-angstrom-linux-gnueabi-g++
else
	CXX=g++
endif

ifeq (${DEBUG},yes)
        CXXFLAGS += -DDEBUG -g
endif

all: ${OBJECTS}
	${CXX} -o ${BUILD_DIR}/${EXECUTABLE} ${OBJECTS} ${CXXFLAGS}

${BUILD_DIR}/%.o: %.cpp ${BUILD_DIR}
	${CXX} -c -o $@ $< ${CXXFLAGS}

clean: 
	@rm -rf ${BUILD_DIR}

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

${BUILD_DIR}:
	mkdir -p ${BUILD_DIR}
