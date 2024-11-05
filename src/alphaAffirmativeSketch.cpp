# include "alphaAffirmativeSketch.h"

// Getter implementation
std::vector<hash_t> AlphaAffirmativeSketch::get() const {
    std::vector<hash_t> vec;
    for (auto it = data_.begin(); it != data_.end(); it++) {
        vec.push_back(*it);
    }
    return vec;
}

// Adds a single element to the vector
void AlphaAffirmativeSketch::add(hash_t value) {
    
    // if value in sketch, do nothing
    if (data_.find(value) != data_.end()) {
        return;
    }

    // if this is the first element
    if (data_.size() == 0) {
        data_.insert(value);
        quantile_it = data_.begin();
        largest_it = data_.begin();
        return;
    }

    // ------ acceptance region1 ---- | ---- acceptance region2 ---- | ---- rejection region ----
    // -------------------------- threshold2 ------------------ threshold1 ----------------------

    hash_t threshold1_ = *largest_it;
    hash_t threshold2_ = *quantile_it;
    if (value > threshold1_) {
        return;
    } else if (value > threshold2_) {
        data_.insert(value);
        data_.erase(*data_.rbegin());
        largest_it = std::prev(data_.end());
    } else {
        data_.insert(value);
        size_t num_elements = data_.size();
        size_t quantile_position = static_cast<size_t>(std::ceil(alpha * (num_elements-1));
        auto current_quantile_position = std::distance(data_.begin(), quantile_it);

        if (current_quantile_position > quantile_position) {
            --quantile_it;
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
double AlphaAffirmativeSketch::jaccard(const AlphaAffirmativeSketch& other) const {
    
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