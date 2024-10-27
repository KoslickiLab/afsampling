#include "Sketch.h"

// Getter implementation
const std::vector<hash_t>& Sketch::get() const {
    return data_;
}

// Setter implementation
void Sketch::set(const std::vector<hash_t>& vec) {
    data_ = vec;
}

// Adds a single element to the vector
void Sketch::add(hash_t value) {
    data_.push_back(value);
}
