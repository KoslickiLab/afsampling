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



int main(int argc, char* argv[]) {
    
    parse_arguments(argc, argv);

    // show arguments from the global struct
    cout << "Scaled: " << arguments.scaled << endl;
    cout << "k: " << arguments.k << endl;

    vector<int> sizes = {10000, 100000, 1000000, 10000000, 100000000};
    int max_size = 1000000000;
    cout << "Sizes of the original sets considered: " << endl;
    for (int size : sizes) {
        cout << size << " ";
    }
    cout << endl;

    for (int size : sizes) {

        vector<int> fmh_sketch_sizes;
        vector<int> aff_sketch_sizes;
        vector<int> alpha_aff_sketch_sizes;

        for (int i = 0; i < arguments.num_trials; i++) {

            // create a set of size 'size' randomly
            vector<int> original_set;
            for (int i = 0; i < size; i++) {
                original_set.push_back( rand() % max_size );
            }

            // create sketches
            FracMinHashSketch fmh_sketch(arguments.scaled);
            AffirmativeSketch aff_sketch(arguments.k);
            AlphaAffirmativeSketch alpha_aff_sketch(arguments.alpha);
            
            for (int value : original_set) {
                auto hash_value = mmh3(&value, sizeof(value), 0);
                fmh_sketch.add(hash_value);
                aff_sketch.add(hash_value);
                alpha_aff_sketch.add(hash_value);
            }

            fmh_sketch_sizes.push_back(fmh_sketch.get().size());
            aff_sketch_sizes.push_back(aff_sketch.get().size());
            alpha_aff_sketch_sizes.push_back(alpha_aff_sketch.get().size());

        }

        // print the average and std of the sizes of the sketches
        double fmh_avg = 0;
        double aff_avg = 0;
        double alpha_aff_avg = 0;
        for (int i = 0; i < arguments.num_trials; i++) {
            fmh_avg += fmh_sketch_sizes[i];
            aff_avg += aff_sketch_sizes[i];
            alpha_aff_avg += alpha_aff_sketch_sizes[i];
        }

        fmh_avg /= arguments.num_trials;
        aff_avg /= arguments.num_trials;
        alpha_aff_avg /= arguments.num_trials;

        double fmh_std = 0;
        double aff_std = 0;
        double alpha_aff_std = 0;

        for (int i = 0; i < arguments.num_trials; i++) {
            fmh_std += (fmh_sketch_sizes[i] - fmh_avg) * (fmh_sketch_sizes[i] - fmh_avg);
            aff_std += (aff_sketch_sizes[i] - aff_avg) * (aff_sketch_sizes[i] - aff_avg);
            alpha_aff_std += (alpha_aff_sketch_sizes[i] - alpha_aff_avg) * (alpha_aff_sketch_sizes[i] - alpha_aff_avg);
        }

        fmh_std = sqrt(fmh_std / arguments.num_trials);
        aff_std = sqrt(aff_std / arguments.num_trials);
        alpha_aff_std = sqrt(alpha_aff_std / arguments.num_trials);

        cout << size << "," << fmh_avg << "," << fmh_std << "," << aff_avg << "," << aff_std << "," << alpha_aff_avg << "," << alpha_aff_std << endl;


    }


    return 0;
}