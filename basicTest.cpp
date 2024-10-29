# include <iostream>
# include <vector>
# include <cstdlib>
# include <string>

# include "src/AffirmativeSketch.h"
# include "mmh3/MurMurHash3.h"
# include "src/FracMinHashSketch.h"

#define SEED 0

int main() {
    FracMinHashSketch fmh_sketch(10);
    AffirmativeSketch aff_sketch(10);

    for (int i = 0; i < 1000; i++) {
        uint64_t hash_value = mmh3(&i, sizeof(i), SEED);
        fmh_sketch.add(hash_value);
        aff_sketch.add(hash_value);
    }

    // Print the number of elements in the sketches
    std::cout << "Number of elements in the FMH sketch: " << fmh_sketch.size() << std::endl;
    std::cout << "Number of elements in the Affirmative sketch: " << aff_sketch.size() << std::endl;

    return 0;
}