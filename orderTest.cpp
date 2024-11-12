# include <iostream>
# include <vector>
# include <cstdlib>
# include <string>
# include <cmath>
# include <chrono>
# include <random>
# include <algorithm>
# include <set>
# include <map>
# include <cassert>
# include <tuple>
# include <cmath>
# include <stdexcept>
# include <string>

# include "src/AffirmativeSketch.h"
# include "mmh3/MurMurHash3.h"
# include "src/FracMinHashSketch.h"
# include "src/alphaAffirmativeSketch.h"

# include "argparse/argparse.hpp"

using namespace std;

struct Arguments {
    uint k;
    uint num_trials;
    uint num_max_elements;
};

typedef Arguments Arguments;

Arguments arguments;

void parse_args(int argc, char** argv) {
    argparse::ArgumentParser program("orderTest", "0.0.0");

    program.add_argument("-k", "--k")
        .help("Value for k in AffirmativeSketch")
        .scan<'i', int>()
        .default_value(100);

    program.add_argument("-n", "--num-trials")
        .help("Number of trials")
        .scan<'i', int>()
        .default_value(100);

    program.add_argument("-m", "--num-max-elements")
        .help("Number of maximum elements")
        .scan<'i', int>()
        .default_value(1000);

    program.parse_args(argc, argv);

    arguments.k = program.get<int>("-k");
    arguments.num_trials = program.get<int>("-n");
    arguments.num_max_elements = program.get<int>("-m");
}


pair<double, double> get_mean_std_of_sketch_sizes(vector<int> sketch_sizes) {

    // calculate mean and standard deviation of the sketch sizes
    double mean = 0;
    for (int size : sketch_sizes) {
        mean += size;
    }
    mean /= arguments.num_trials;
    double std = 0;
    for (int size : sketch_sizes) {
        std += (size - mean) * (size - mean);
    }
    std /= arguments.num_trials;
    std = sqrt(std);

    return make_pair(mean, std);
}


int main(int argc, char** argv) {

    try {
        parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        exit(1);
    }

    cout << "k: " << arguments.k << endl;
    cout << "num_trials: " << arguments.num_trials << endl;
    cout << "num_max_elements: " << arguments.num_max_elements << endl;

    vector<int> sketch_sizes_ascending;
    vector<int> sketch_sizes_descending;
    vector<int> sketch_sizes_random;

    vector<int> all_elements_random;
    for (int i = 0; i < arguments.num_max_elements; i++) {
        all_elements_random.push_back(i);
    }

    for (int i = 0; i < arguments.num_trials; i++) {

        shuffle(all_elements_random.begin(), all_elements_random.end(), default_random_engine());

        AffirmativeSketch sketch_ascending(arguments.k);
        AffirmativeSketch sketch_descending(arguments.k);
        AffirmativeSketch sketch_random(arguments.k);

        for (int j = 0; j < arguments.num_max_elements; j++) {
            sketch_ascending.add(j);
            sketch_descending.add(arguments.num_max_elements - j);
            sketch_random.add(all_elements_random[j]);
        }

        sketch_sizes_ascending.push_back(sketch_ascending.get().size());
        sketch_sizes_descending.push_back(sketch_descending.get().size());
        sketch_sizes_random.push_back(sketch_random.get().size());

    }

    auto mean_std_ascending = get_mean_std_of_sketch_sizes(sketch_sizes_ascending);
    auto mean_std_descending = get_mean_std_of_sketch_sizes(sketch_sizes_descending);
    auto mean_std_random = get_mean_std_of_sketch_sizes(sketch_sizes_random);

    cout << "Ascending: " << mean_std_ascending.first << " " << mean_std_ascending.second << endl;
    cout << "Descending: " << mean_std_descending.first << " " << mean_std_descending.second << endl;
    cout << "Random: " << mean_std_random.first << " " << mean_std_random.second << endl;


    return 0;

}