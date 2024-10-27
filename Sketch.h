#ifndef SKETCH_H
#define SKETCH_H

#include <vector>

// Define a type alias for unsigned long long int
typedef unsigned long long int hash_t;

class Sketch {
public:
    // Constructor
    Sketch() = default;  // Default constructor

    // Getter: returns a const reference to the vector
    const std::vector<hash_t>& get() const;

    // Setter: sets the entire vector
    void set(const std::vector<hash_t>& vec);

    // Adds a single element to the vector
    void add(hash_t value);

private:
    std::vector<hash_t> data_;  // Vector to store data of type hash_t
};

#endif // SKETCH_H
