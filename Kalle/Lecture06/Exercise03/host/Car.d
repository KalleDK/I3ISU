host/Car.o: src/Car.cpp src/Car.hpp src/Message.hpp src/Request.hpp \
 src/AI.hpp src/MsgQueue.hpp src/Timer.hpp src/IDList.hpp src/Event.hpp
	${CXX} -c -o $@ $< ${CXXFLAGS}
