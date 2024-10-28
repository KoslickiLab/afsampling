#ifndef FRACMINHASH_SKETCH_H
#define FRACMINHASH_SKETCH_H

#include <vector>
#include <map>

#include "Sketch.h"

typedef unsigned long long int hash_t;

// FracMinHashSketch class will be derived from Sketch class
class FracMinHashSketch : public Sketch {
public:
    FracMinHashSketch(size_t scaled) : scaled_(scaled) {
        uint64_t largest_value = 0xFFFFFFFFFFFFFFFF;
        threshold_ = std::round( (long double)largest_value / (long double)scaled_ );
    }

    std::vector<hash_t> get() const;

    void set(const std::vector<hash_t>& vec);

    void add(hash_t value);

private:
    hash_t threshold_ = 0;  
    size_t scaled_ = 0;
};

#endif // FRACMINHASH_SKETCH_H