# include "AffirmativeSketch.h"

// Getter implementation
std::vector<hash_t> AffirmativeSketch::get() const {
    // call base class get method
    return Sketch::get();
}

// Setter implementation
void AffirmativeSketch::set(const std::vector<hash_t>& vec) {
    // call base class set method
    Sketch::set(vec);
}

// Adds a single element to the vector
void AffirmativeSketch::add(hash_t value) {
    // call base class add method
    Sketch::add(value);
}