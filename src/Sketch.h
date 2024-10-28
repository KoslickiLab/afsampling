#ifndef SKETCH_H
#define SKETCH_H

#include <vector>
#include <map>

typedef unsigned long long int hash_t;

class Sketch {
public:
    Sketch() = default;  // Default constructor

    std::vector<hash_t> get() const;

    void set(const std::vector<hash_t>& vec);

    void add(hash_t value);

    size_t size() const;

private:
    std::map<hash_t, int> data_;  // Map to store data of type hash_t
};

#endif // SKETCH_H
