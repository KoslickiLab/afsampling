# include <iostream>
# include <vector>
# include <cstdlib>
# include <string>

# include "src/AffirmativeSketch.h"
# include "mmh3/MurMurHash3.h"
# include "src/FracMinHashSketch.h"
# include "src/alphaAffirmativeSketch.h"

# include "argparse/argparse.hpp"

using namespace std;


struct Arguments {
    uint scaled;
    uint k;
    uint num_trials;
    double alpha;
};

typedef Arguments Arguments;

Arguments arguments;

/*
This function parses the arguments, and sets the global struct arguments.
The plan is to make this struct available to all functions in the program.
*/
void parse_arguments(int argc, char* argv[]) {
    // Define the parser
    argparse::ArgumentParser program("sketchSizeTest", "0.0.0");

    // Define the arguments
    // scaled
    program.add_argument("-s", "--scaled")
        .help("Scaled value for FracMinHashSketch")
        .scan<'i', int>()
        .default_value(1000);

    // k for AffirmativeSketch
    program.add_argument("-k", "--k")
        .help("Value for k in AffirmativeSketch")
        .scan<'i', int>()
        .default_value(100);

    // double alpha for alphaAffirmativeSketch
    program.add_argument("-a", "--alpha")
        .help("Value for alpha in alphaAffirmativeSketch")
        .scan<'g', double>()
        .default_value(0.7);

    // number of trials in each setting
    program.add_argument("-n", "--num_trials")
        .help("Number of trials in each setting")
        .scan<'i', int>()
        .default_value(20);

        
    // Parse the arguments
    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        exit(1);
    }

    // set the arguments in the global struct
    arguments.scaled = program.get<int>("--scaled");
    arguments.k = program.get<int>("--k");
    arguments.num_trials = program.get<int>("--num_trials");
    arguments.alpha = program.get<double>("--alpha");

}


pair<double, double> get_mean_std_of_sketch_sizes_fmh(int set_size) {
    
    vector<int> sketch_sizes;
    for (int i = 0; i < arguments.num_trials; i++) {
        FracMinHashSketch sketch(arguments.scaled);

        for (int j = 0; j < set_size; j++) {
            sketch.add(mmh3(&j, sizeof(j), i));
        }
        sketch_sizes.push_back(sketch.get().size());
    }

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


pair<double, double> get_mean_std_of_sketch_sizes_as(int set_size) {
    
    vector<int> sketch_sizes;
    for (int i = 0; i < arguments.num_trials; i++) {
        AffirmativeSketch sketch(arguments.k);

        for (int j = 0; j < set_size; j++) {
            sketch.add(mmh3(&j, sizeof(j), i));
        }
        sketch_sizes.push_back(sketch.get().size());
    }

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


pair<double, double> get_mean_std_of_sketch_sizes_aas(int set_size) {
    
    vector<int> sketch_sizes;
    for (int i = 0; i < arguments.num_trials; i++) {
        AlphaAffirmativeSketch sketch(arguments.alpha);

        for (int j = 0; j < set_size; j++) {
            sketch.add(mmh3(&j, sizeof(j), i));
        }
        sketch_sizes.push_back(sketch.get().size());
    }

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



int main(int argc, char* argv[]) {
    
    parse_arguments(argc, argv);

    // show arguments from the global struct
    cout << "Scaled: " << arguments.scaled << endl;
    cout << "k: " << arguments.k << endl;
    cout << "alpha: " << arguments.alpha << endl;

    vector<int> sizes = {10000, 100000, 1000000, 10000000, 100000000};
    int max_size = 1000000000;
    auto fmh_start = chrono::high_resolution_clock::now();
    for (int size : sizes) {
        auto [mean, std] = get_mean_std_of_sketch_sizes_fmh(size);
        cout << "FracMinHashSketch: " << size << " " << mean << " " << std << endl;
    }
    auto fmh_end = chrono::high_resolution_clock::now();
    auto fmh_duration = chrono::duration_cast<chrono::milliseconds>(fmh_end - fmh_start);
    cout << "FracMinHashSketch took " << fmh_duration.count() << " milliseconds" << endl;

    auto as_start = chrono::high_resolution_clock::now();
    for (int size : sizes) {
        auto [mean, std] = get_mean_std_of_sketch_sizes_as(size);
        cout << "AffirmativeSketch: " << size << " " << mean << " " << std << endl;
    }
    auto as_end = chrono::high_resolution_clock::now();
    auto as_duration = chrono::duration_cast<chrono::milliseconds>(as_end - as_start);
    cout << "AffirmativeSketch took " << as_duration.count() << " milliseconds" << endl;

    auto aas_start = chrono::high_resolution_clock::now();
    for (int size : sizes) {
        auto [mean, std] = get_mean_std_of_sketch_sizes_aas(size);
        cout << "AlphaAffirmativeSketch: " << size << " " << mean << " " << std << endl;
    }
    auto aas_end = chrono::high_resolution_clock::now();
    auto aas_duration = chrono::duration_cast<chrono::milliseconds>(aas_end - aas_start);
    cout << "AlphaAffirmativeSketch took " << aas_duration.count() << " milliseconds" << endl;


    return 0;
}