# include <iostream>
# include <vector>
# include <cstdlib>
# include <string>

# include "src/AffirmativeSketch.h"
# include "src/MurMurHash3.h"
# include "src/FracMinHashSketch.h"

#define SEED 0

int main() {
    // Create an instance of the Sketch class
    FracMinHashSketch sketch(100);

    // Create 1000 random 64 bit uintegers, and add them to the sketch
    for (int i = 0; i < 1000; i++) {
        uint64_t hash_value = mmh3(&i, sizeof(i), SEED);
        sketch.add(hash_value);
    }

    // Get the vector
    const std::vector<hash_t>& vec = sketch.get();

    // Print the number of elements in the vector
    std::cout << "Number of elements in the sketch: " << vec.size() << std::endl;


    return 0;
}