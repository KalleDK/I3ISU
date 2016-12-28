SOURCES = main.cpp part1.cpp part2.cpp
OBJECTS = $(SOURCES:.cpp=.o)
DEPS = $(SOURCES:.cpp=.d)
EXE = Parts
CXXFLAGS = -I.

$(EXE): $(DEPS) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

%.d: %.cpp
	$(CXX) -MT $(@:.d=.o) -MM $(CXXFLAGS) $^ > $@

clean: ;
	@rm $(EXE) $(OBJECTS) $(DEPS)

help: ;
	@echo "Available targets:	Action:"
	@echo "Parts			build target"
	@echo "clean			delete o and target"

-include $(DEPS)
