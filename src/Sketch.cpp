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


// Returns the size of the vector
size_t Sketch::size() const {
    return data_.size();
}


// Returns the Jaccard similarity between two sketches
double Sketch::jaccard(const Sketch& other) const {
    // Create a set to store the union of the two sketches
    std::set<hash_t> union_set;
    // Iterate over the keys of the current sketch and add them to the union set
    for (const auto& pair : data_) {
        union_set.insert(pair.first);
    }
    // Iterate over the keys of the other sketch and add them to the union set
    for (const auto& pair : other.data_) {
        union_set.insert(pair.first);
    }

    // Create a set to store the intersection of the two sketches
    std::set<hash_t> intersection_set;
    // Iterate over the keys of the current sketch
    for (const auto& pair : data_) {
        // If the key is present in the other sketch, add it to the intersection set
        if (other.data_.count(pair.first) > 0) {
            intersection_set.insert(pair.first);
        }
    }

    // Calculate the Jaccard similarity
    double jaccard = static_cast<double>(intersection_set.size()) / union_set.size();
    return jaccard;
}