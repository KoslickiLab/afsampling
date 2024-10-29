CXX = g++
CXXFLAGS = -std=c++11
SRC = src/AffirmativeSketch.cpp src/Sketch.cpp src/MurMurHash3.cpp src/FracMinHashSketch.cpp
OBJ = $(SRC:.cpp=.o)
TARGET1 = basicTest
TARGET2 = sketchSizeTest

all: $(TARGET1) $(TARGET2)

$(TARGET1): basicTest.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET2): sketchSizeTest.o $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET1) $(TARGET2) $(OBJ) *.o

