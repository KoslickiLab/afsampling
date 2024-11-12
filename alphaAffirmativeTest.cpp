#include "src/alphaAffirmativeSketch.h"
#include "mmh3/MurMurHash3.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    
    vector<double> alpha_values = {0.1, 0.3, 0.5, 0.7};
    vector<int> num_elements_vector = {10000, 100000, 1000000, 10000000, 100000000};
    int num_runs = 5;

    for (int num_elements : num_elements_vector) {
        for (double alpha : alpha_values) {
            for (int seed = 0; seed < num_runs; seed++) {
                AlphaAffirmativeSketch sketch(alpha);

                for (int i = 0; i < num_elements; i++) {
                    sketch.add(mmh3(&i, sizeof(i), seed));
                }

                cout << "Number of elements: " << num_elements << endl;
                cout << "Alpha: " << alpha << endl;
                cout << "Seed: " << seed << endl;
                cout << "Size of sketch: " << sketch.get().size() << endl;
            }
        }
    }

    return 0;
}