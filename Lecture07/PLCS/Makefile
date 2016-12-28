MKDIR=mkdir -p
ECHO=echo
RM=rm -rf

BASEPATH=../OSApiStudent
ARGV=
ARCH=host
BUILD_DIR=${ARCH}
SRC_DIR=src
SOURCES=${SRC_DIR}/garage.cpp ${SRC_DIR}/car.cpp ${SRC_DIR}/door.cpp ${SRC_DIR}/messageHandler.cpp ${SRC_DIR}/main.cpp 
OBJECTS=${SOURCES:${SRC_DIR}/%.cpp=${BUILD_DIR}/%.o}
DEPS_CPP=${SOURCES:${SRC_DIR}/%.cpp=${BUILD_DIR}/%.dpp}
DEPS=${DEPS_CPP:${SRC_DIR}/%.c=${BUILD_DIR}/%.d}
EXECUTABLE=main
CXXFLAGS=-Wall -D_REENTRANT -DOS_LINUX -I$(BASEPATH)/inc
MAKEFILE_TARGETS_WITHOUT_INCLUDE := clean help 

ifeq (${ARCH},target)
	CXXFLAGS+= -std=c++0x
	CXX=arm-angstrom-linux-gnueabi-g++
	LIBPATH=$(BASEPATH)/lib/target/release
else
	CXXFLAGS+= -std=c++11 -O2
	CXX=g++
	LIBPATH=$(BASEPATH)/lib/host/release
endif

ifdef DEBUG
	CXXFLAGS+= -DDEBUG -g -ggdb -O0
	LIBPATH=$(BASEPATH)/lib/target/debug
endif

.PHONY: clean help run

${EXECUTABLE}: ${OBJECTS}
	${CXX} -o ${BUILD_DIR}/${EXECUTABLE} ${OBJECTS} -L$(LIBPATH) -lOSApi -lrt -lpthread

${BUILD_DIR}/%.d: ${SRC_DIR}/%.c
	@${MKDIR} ${BUILD_DIR}
	@${CXX} -MT $(@:.d=.o) -MM $< > $@
	@${ECHO} '	$${CXX} -c -o $$@ $$< $${CXXFLAGS}' >> $@

${BUILD_DIR}/%.dpp: ${SRC_DIR}/%.cpp
	@${MKDIR} ${BUILD_DIR}
	@${CXX} -MT $(@:.dpp=.o) -MM $< > $@
	@${ECHO} '	$${CXX} -c -o $$@ $$< $${CXXFLAGS}' >> $@

clean:
	@if [ -d "${BUILD_DIR}" ]; then ${RM} -v  "${BUILD_DIR}"; fi

run: ${EXECUTABLE}
	./${BUILD_DIR}/${EXECUTABLE} ${ARGV}

help:
	@${ECHO} "Help"

ifeq ($(filter $(MAKECMDGOALS),$(MAKEFILE_TARGETS_WITHOUT_INCLUDE)),)
-include $(DEPS)
endif
