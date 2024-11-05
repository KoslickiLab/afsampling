CXX = g++
CXXFLAGS = -std=c++17 -w -Wall -O3 -Wsign-compare

# Directories
SRC_DIR = src
MMH3_DIR = mmh3
BIN_DIR = bin

# Source files
SRC_FILES = $(SRC_DIR)/Sketch.cpp $(SRC_DIR)/FracMinHashSketch.cpp $(SRC_DIR)/AffirmativeSketch.cpp $(MMH3_DIR)/MurMurHash3.cpp $(SRC_DIR)/alphaAffirmativeSketch.cpp

# Object files
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Target programs
TARGETS = $(BIN_DIR)/basicTest $(BIN_DIR)/sketchSizeTest $(BIN_DIR)/accuracyTest $(BIN_DIR)/accuracyTest2 $(BIN_DIR)/alphaTest

# Default rule
all: $(TARGETS)

# Rule to build basicTest
$(BIN_DIR)/basicTest: $(OBJ_FILES) $(BIN_DIR)/basicTest.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build sketchSizeTest
$(BIN_DIR)/sketchSizeTest: $(OBJ_FILES) $(BIN_DIR)/sketchSizeTest.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build accuracyTest
$(BIN_DIR)/accuracyTest: $(OBJ_FILES) $(BIN_DIR)/accuracyTest.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build accuracyTest2
$(BIN_DIR)/accuracyTest2: $(OBJ_FILES) $(BIN_DIR)/accuracyTest2.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build alphaTest
$(BIN_DIR)/alphaTest: $(OBJ_FILES) $(BIN_DIR)/alphaTest.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Create the bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Rule to build object files
$(OBJ_FILES): %.o: %.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule to build object files for test programs
$(BIN_DIR)/basicTest.o: basicTest.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/sketchSizeTest.o: sketchSizeTest.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/accuracyTest.o: accuracyTest.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/accuracyTest2.o: accuracyTest2.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/alphaTest.o: alphaAffirmativeTest.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean up
clean:
	rm -f $(OBJ_FILES) $(BIN_DIR)/*.o $(TARGETS)

clean-object:
	rm -f $(OBJ_FILES)

.PHONY: all clean
