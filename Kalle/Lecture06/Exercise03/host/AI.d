host/AI.o: src/AI.cpp src/AI.hpp src/MsgQueue.hpp src/Message.hpp
	${CXX} -c -o $@ $< ${CXXFLAGS}
