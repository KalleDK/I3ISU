host/main.o: src/main.cpp src/MsgQueue.hpp src/Message.hpp
	${CXX} -c -o $@ $< ${CXXFLAGS}
