MAINPROG := DualNumbers
TESTPROG := TestDuals
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wpedantic -fsanitize=address,undefined
CPPFLAGS := -MMD -MP

# Explicitly set source files for each program
MAIN_SOURCES := Duals.cpp
TEST_SOURCES := TestDuals.cpp

# Object files for each program
MAIN_OBJECTS := $(MAIN_SOURCES:.cpp=.o)
TEST_OBJECTS := $(TEST_SOURCES:.cpp=.o)

# Dependency files for include header tracking
DEPS := $(MAIN_OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

.PHONY: all clean test

# Default target builds the main program
all: $(MAINPROG)

# Test target builds and runs the test program
test: $(TESTPROG)

# Rule to link the main program executable
$(MAINPROG): $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to link the test program executable and run it
$(TESTPROG): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Include the dependency files
-include $(DEPS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Clean target for removing build artifacts
clean:
	rm -f $(MAIN_OBJECTS) $(TEST_OBJECTS) $(DEPS) $(MAINPROG) $(TESTPROG)
