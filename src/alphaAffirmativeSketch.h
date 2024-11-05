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
#include <cassert>
#include <set>

typedef unsigned long long int hash_t;

// AffirmativeSketch class will be derived from Sketch class
class AlphaAffirmativeSketch {
public:
    AlphaAffirmativeSketch(double alpha) : alpha(alpha) {
        assert(alpha >= 0 && alpha <= 1);
    }

    std::vector<hash_t> get() const;

    void set(const std::vector<hash_t>& vec);

    void add(hash_t value);

    double jaccard(const AlphaAffirmativeSketch& other) const;

    void print() const;

private:
    double alpha;
    std::multiset<hash_t> data_;
    std::multiset<hash_t>::iterator quantile_it;
    std::multiset<hash_t>::iterator largest_it;

};

#endif // ALPHA_AFFIRMATIVE_SKETCH_H