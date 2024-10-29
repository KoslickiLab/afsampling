CXX = g++
CXXFLAGS = -std=c++11
SRC = basicTest.cpp src/AffirmativeSketch.cpp src/Sketch.cpp src/MurMurHash3.cpp src/FracMinHashSketch.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = basicTest 

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)