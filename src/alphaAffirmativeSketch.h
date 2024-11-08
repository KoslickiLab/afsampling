#ifndef ALPHA_AFFIRMATIVE_SKETCH_H
#define ALPHA_AFFIRMATIVE_SKETCH_H

#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <limits>

#include "Sketch.h"

typedef unsigned long long int hash_t;

// AffirmativeSketch class will be derived from Sketch class
class AlphaAffirmativeSketch : public Sketch {
public:
    AlphaAffirmativeSketch(double alpha) : alpha(alpha) {
    }

    std::vector<hash_t> get() const;

    void set(const std::vector<hash_t>& vec);

    void add(hash_t value);

    double jaccard(const Sketch& other) const;

private:
    double alpha;
};

#endif // ALPHA_AFFIRMATIVE_SKETCH_H