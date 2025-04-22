CXX = g++
CXXFLAGS = -Wall -std=c++11
SOURCES = TwoPipesTwoChildren.cpp TwoPipesThreeChildren.cpp DynPipe.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLES = TwoPipesTwoChildren TwoPipesThreeChildren dynpipe

all: $(EXECUTABLES)

TwoPipesTwoChildren: TwoPipesTwoChildren.o
	$(CXX) $(CXXFLAGS) -o $@ $^

TwoPipesThreeChildren: TwoPipesThreeChildren.o
	$(CXX) $(CXXFLAGS) -o $@ $^

dynpipe: DynPipe.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLES)

.PHONY: all clean
