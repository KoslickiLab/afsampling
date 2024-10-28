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
        threshold1_ = threshold2_ = data_.begin()->first;
    
    // for the rest:
    } else {
        if (value < threshold1_) {
            // if < threshold1, then do not add to sketch
            return;
        } else if (value < threshold2_) {
            // if < threshold2, add to sketch and remove the first element
            Sketch::add(value);
            data_.erase(data_.begin());
            threshold1_ = data_.begin()->first;
        } else {
            // if > threshold2, add to sketch and update threshold2 = the kth largest element
            Sketch::add(value);
            auto it = data_.rbegin();
            std::advance(it, k - 1);
            threshold2_ = it->first;
        }
    }
}

// Setter implementation
void AffirmativeSketch::set(const std::vector<hash_t>& vec) {
    // clear the map
    data_.clear();
    for (hash_t value : vec) {
        add(value);
    }
}

