CXX = g++
CXXFLAGS = -std=c++11
SRC = main.cpp src/AffirmativeSketch.cpp src/Sketch.cpp src/MurMurHash3.cpp src/FracMinHashSketch.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = sketchTester

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)