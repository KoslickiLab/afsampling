# include "AffirmativeSketch.h"

// Getter implementation
std::vector<hash_t> AffirmativeSketch::get() const {
    // call base class get method
    return Sketch::get();
}

// Adds a single element to the vector
void AffirmativeSketch::add(hash_t value) {
    // if value in sketch, do nothing
    if (data_.find(value) != data_.end()) {
        return;
    }

    // for the first k elements, add them to the sketch
    if (data_.size() < k) {
        Sketch::add(value);
        // get the last element as the thresholds
        auto it = data_.rbegin();
        threshold1_ = it->first;
        threshold2_ = it->first;
    
    // ------ acceptance region1 ---- | ---- acceptance region2 ---- | ---- rejection region ----
    // -------------------------- threshold2 ------------------ threshold1 ----------------------

    // for the rest:
    } else {
        if (value > threshold1_) {
            // if > threshold1, then do not add to sketch
            return;
        } else if (value > threshold2_) {
            // if > threshold2, add to sketch and remove the first element
            Sketch::add(value);
            data_.erase(data_.rbegin()->first);
            threshold1_ = data_.rbegin()->first;
        } else {
            // if <= threshold2, add to sketch and update threshold2 = the kth smallest element
            Sketch::add(value);
            auto it = data_.begin();
            std::advance(it, k - 1);
            threshold2_ = it->first;
        }
    }
}

// Setter implementation, not expected to be used
void AffirmativeSketch::set(const std::vector<hash_t>& vec) {
    // clear the map
    data_.clear();
    for (hash_t value : vec) {
        add(value);
    }
}


// Jaccard implementation
double AffirmativeSketch::jaccard(const Sketch& other) const {
    
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