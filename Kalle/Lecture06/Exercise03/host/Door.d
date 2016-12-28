host/Door.o: src/Door.cpp src/Door.hpp src/IDList.hpp src/Message.hpp \
 src/Request.hpp src/AI.hpp src/MsgQueue.hpp
	${CXX} -c -o $@ $< ${CXXFLAGS}
