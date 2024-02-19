MAINPROG := DualNumbers
TESTPROG := TestDuals
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wpedantic -fsanitize=address,undefined
CPPFLAGS := -MMD -MP

# Source files for the main program (excluding test files)
MAIN_SOURCES := $(wildcard *.cpp)
MAIN_SOURCES := $(filter-out $(TESTPROG).cpp,$(MAIN_SOURCES))
MAIN_OBJECTS := $(MAIN_SOURCES:.cpp=.o)
DEPS := $(MAIN_OBJECTS:.o=.d)

# Source files for the test program
TEST_SOURCES := $(filter-out $(MAINPROG).cpp,$(wildcard *.cpp))
TEST_OBJECTS := $(TEST_SOURCES:.cpp=.o)
TEST_DEPS := $(TEST_OBJECTS:.o=.d)

.PHONY: all clean test

all: $(MAINPROG)

$(MAINPROG): $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(TESTPROG)

$(TESTPROG): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	./$(TESTPROG)

-include $(DEPS) $(TEST_DEPS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(MAIN_OBJECTS) $(TEST_OBJECTS) $(DEPS) $(TEST_DEPS) $(MAINPROG) $(TESTPROG)
