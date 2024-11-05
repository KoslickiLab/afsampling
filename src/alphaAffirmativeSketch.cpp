# include "alphaAffirmativeSketch.h"

// Getter implementation
std::vector<hash_t> AlphaAffirmativeSketch::get() const {
    // call base class get method
    return Sketch::get();
}

// Adds a single element to the vector
void AlphaAffirmativeSketch::add(hash_t value) {
    // if value in sketch, do nothing
    if (data_.find(value) != data_.end()) {
        return;
    }

    // add the first element
    if (data_.size() == 0) {
        Sketch::add(value);

    // ------ acceptance region1 ---- | ---- acceptance region2 ---- | ---- rejection region ----
    // -------------------------- threshold2 ------------------ threshold1 ----------------------
    // for the rest:
    } else {

        size_t n = data_.size();
        size_t k = static_cast<size_t>(std::floor(alpha * n));
        auto it_reverse = data_.rbegin();
        hash_t threshold1_ = it_reverse->first;
        if (k != 0) std::advance(it_reverse, k-1);
        hash_t threshold2_ = it_reverse->first;

        if (value > threshold1_) {
            return;
        } else if (value > threshold2_) {
            Sketch::add(value);
            data_.erase(data_.rbegin()->first);
        } else {
            Sketch::add(value);
        }
    }
}

// Setter implementation, not expected to be used
void AlphaAffirmativeSketch::set(const std::vector<hash_t>& vec) {
    // clear the map
    data_.clear();
    for (hash_t value : vec) {
        add(value);
    }
}


// Jaccard implementation
double AlphaAffirmativeSketch::jaccard(const Sketch& other) const {
    
    std::vector<hash_t> this_sketch = get();
    std::vector<hash_t> other_sketch = other.get();

    size_t this_size = this_sketch.size();
    size_t other_size = other_sketch.size();

    // get the smallest common hash
    size_t i = this_size - 1, j = other_size - 1;
    bool found = false;
    hash_t largest_common_hash = -1;
    while (i > 0 && j > 0) {
        if (this_sketch[i] == other_sketch[j]) {
            found = true;
            largest_common_hash = this_sketch[i];
            break;
        } else if (this_sketch[i] > other_sketch[j]) {
            i--;
        } else {
            j--;
        }
    }

    // if no common hash, return 0
    if (!found) {
        return 0;
    }

    std::set<hash_t> union_set;
    for (hash_t value : this_sketch) {
        if (value > largest_common_hash) {
            break;
        }
        union_set.insert(value);
    }
    for (hash_t value : other_sketch) {
        if (value > largest_common_hash) {
            break;
        }
        union_set.insert(value);
    }

    std::set<hash_t> intersection_set;
    for (hash_t value : this_sketch) {
        if (value > largest_common_hash) {
            break;
        }
        if (std::find(other_sketch.begin(), other_sketch.end(), value) != other_sketch.end()) {
            intersection_set.insert(value);
        }
    }

    double jaccard = static_cast<double>(intersection_set.size()) / union_set.size();
    return jaccard;

}