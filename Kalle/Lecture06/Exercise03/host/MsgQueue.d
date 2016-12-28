host/MsgQueue.o: src/MsgQueue.cpp src/MsgQueue.hpp src/Message.hpp
	${CXX} -c -o $@ $< ${CXXFLAGS}
