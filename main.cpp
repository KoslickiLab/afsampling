# include <iostream>
# include <vector>

# include "Sketch.h"

int main() {
    // Create an instance of the Sketch class
    Sketch sketch;

    // Add some elements to the vector
    sketch.add(1);
    sketch.add(3);
    sketch.add(5);
    sketch.add(2);

    // Get the vector
    const std::vector<hash_t>& vec = sketch.get();

    // Print the vector
    for (hash_t value : vec) {
        std::cout << value << std::endl;
    }

    return 0;
}