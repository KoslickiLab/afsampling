#ifndef AFFIRMATIVE_SKETCH_H
#define AFFIRMATIVE_SKETCH_H

#include <vector>
#include <map>

#include "Sketch.h"

typedef unsigned long long int hash_t;

// AffirmativeSketch class will be derived from Sketch class
class AffirmativeSketch : public Sketch {
public:
    AffirmativeSketch() = default;  // Default constructor

    std::vector<hash_t> get() const;

    void set(const std::vector<hash_t>& vec);

    void add(hash_t value);

private:
    hash_t threshold1_ = 0;  
    hash_t threshold2_ = 0;
};

#endif // AFFIRMATIVE_SKETCH_H