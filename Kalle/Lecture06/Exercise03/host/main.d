host/main.o: src/main.cpp src/Car.hpp src/Message.hpp src/Request.hpp \
 src/AI.hpp src/MsgQueue.hpp src/Timer.hpp src/IDList.hpp src/Event.hpp \
 src/Door.hpp src/Garage.hpp
	${CXX} -c -o $@ $< ${CXXFLAGS}
