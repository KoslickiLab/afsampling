#include "Sketch.h"

// Getter implementation
std::vector<hash_t> Sketch::get() const {
    // Create a vector to store the keys
    std::vector<hash_t> vec;
    // Iterate over the map and add the keys to the vector
    for (const auto& pair : data_) {
        vec.push_back(pair.first);
    }
    return vec;
}

// Setter implementation
void Sketch::set(const std::vector<hash_t>& vec) {
    // clear the map
    data_.clear();
    for (hash_t value : vec) {
        data_[value]++;
    }
}

// Adds a single element to the vector
void Sketch::add(hash_t value) {
    data_[value]++;
}
