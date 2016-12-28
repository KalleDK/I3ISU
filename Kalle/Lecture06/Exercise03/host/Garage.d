host/Garage.o: src/Garage.cpp src/Garage.hpp src/Door.hpp src/IDList.hpp \
 src/Message.hpp src/Request.hpp src/AI.hpp src/MsgQueue.hpp
	${CXX} -c -o $@ $< ${CXXFLAGS}
