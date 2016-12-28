host/Timer.o: src/Timer.cpp src/Timer.hpp src/IDList.hpp src/AI.hpp \
 src/MsgQueue.hpp src/Message.hpp src/Event.hpp src/Request.hpp
	${CXX} -c -o $@ $< ${CXXFLAGS}
