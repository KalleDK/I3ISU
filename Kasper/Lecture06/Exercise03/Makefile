MKDIR=mkdir -p
ECHO=echo
RM=rm -rf

ARGV=
ARCH=host
BUILD_DIR=${ARCH}
SRC_DIR=src
SOURCES=${SRC_DIR}/main.cpp 
OBJECTS=${SOURCES:${SRC_DIR}/%.cpp=${BUILD_DIR}/%.o}
DEPS=${SOURCES:${SRC_DIR}/%.cpp=${BUILD_DIR}/%.d}
EXECUTABLE=main
CXXFLAGS=-lpthread
MAKEFILE_TARGETS_WITHOUT_INCLUDE := clean help 

ifeq (${ARCH},target)
	CXXFLAGS+= -std=c++0x
	CXX=arm-angstrom-linux-gnueabi-g++
else
	CXXFLAGS+= -std=c++11
	CXX=g++
endif

ifdef DEBUG
	CXXFLAGS+= -DDEBUG -g
endif

.PHONY: clean help run

${EXECUTABLE}: ${OBJECTS}
	${CXX} -o ${BUILD_DIR}/${EXECUTABLE} ${OBJECTS} ${CXXFLAGS}

${BUILD_DIR}/%.d: ${SRC_DIR}/%.cpp
	@${MKDIR} ${BUILD_DIR}
	@${CXX} -MT $(@:.d=.o) -MM $< > $@
	@${ECHO} '	$${CXX} -c -o $$@ $$< $${CXXFLAGS}' >> $@

clean:
	${RM} ${BUILD_DIR}

run: ${EXECUTABLE}
	./${BUILD_DIR}/${EXECUTABLE} ${ARGV}

help:
	@${ECHO} "Help"

ifeq ($(filter $(MAKECMDGOALS),$(MAKEFILE_TARGETS_WITHOUT_INCLUDE)),)
-include $(DEPS)
endif
