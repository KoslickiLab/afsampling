# include <iostream>
# include <vector>
# include <cstdlib>
# include <string>

# include "src/AffirmativeSketch.h"
# include "mmh3/MurMurHash3.h"
# include "src/FracMinHashSketch.h"

# include "argparse/argparse.hpp"

using namespace std;


struct Arguments {
    uint scaled;
    uint k;
    uint num_trials;
    uint size_low;
    uint size_high;
    uint max_size;
};

typedef Arguments Arguments;

Arguments arguments;

/*
This function parses the arguments, and sets the global struct arguments.
The plan is to make this struct available to all functions in the program.
*/
void parse_arguments(int argc, char* argv[]) {
    // Define the parser
    argparse::ArgumentParser program("accuracyTest", "0.0.0");

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

    // number of trials in each setting
    program.add_argument("-n", "--num_trials")
        .help("Number of trials in each setting")
        .scan<'i', int>()
        .default_value(10000);

    // max size
    program.add_argument("-m", "--max_size")
        .help("Max size of the original sets")
        .scan<'i', int>()
        .default_value(2000000000);

    // size range
    program.add_argument("-l", "--size_low")
        .help("Low value of the size of the original sets")
        .scan<'i', int>()
        .default_value(10000);

    program.add_argument("-H", "--size_high")
        .help("High value of the size of the original sets")
        .scan<'i', int>()
        .default_value(1000000000);


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
    arguments.size_low = program.get<int>("--size_low");
    arguments.size_high = program.get<int>("--size_high");
    arguments.max_size = program.get<int>("--max_size");

}

int main(int argc, char* argv[]) {
    
    parse_arguments(argc, argv);

    int size_a = arguments.size_high/2;
    vector<int> set_a;
    for (int i = 0; i < size_a; i++) {
        set_a.push_back( rand() % arguments.max_size );
    }

    // create the sketches for set a
    AffirmativeSketch aff_sketch_a(arguments.k);
    FracMinHashSketch fmh_sketch_a(arguments.scaled);
    Sketch no_subsampling_sketch_a;

    // add the elements to the sketches
    for (int element : set_a) {
        auto hash_value = mmh3(&element, sizeof(element), 0);
        aff_sketch_a.add(hash_value);
        fmh_sketch_a.add(hash_value);
        no_subsampling_sketch_a.add(hash_value);
    }

    cout << "size_a\tsize_b\tfmh_sketch_size_a\tfmh_sketch_size_b\taff_sketch_size_a\taff_sketch_size_b\ttrue_jaccard\taff_jaccard\tfmh_jaccard" << endl;

    for (int i = 0; i < arguments.num_trials; i++) {

        int size_b = rand() % (arguments.size_high - arguments.size_low) + arguments.size_low;
        vector<int> set_b;
        
        for (int i = 0; i < size_b; i++) {
            set_b.push_back( rand() % arguments.max_size );
        }

        // create the sketches for set b
        AffirmativeSketch aff_sketch_b(arguments.k);
        FracMinHashSketch fmh_sketch_b(arguments.scaled);
        Sketch no_subsampling_sketch_b;

        // add the elements to the sketches
        for (int element : set_b) {
            auto hash_value = mmh3(&element, sizeof(element), 0);
            aff_sketch_b.add(hash_value);
            fmh_sketch_b.add(hash_value);
            no_subsampling_sketch_b.add(hash_value);
        }

        double true_jaccard = no_subsampling_sketch_a.jaccard(no_subsampling_sketch_b);
        double aff_jaccard = aff_sketch_a.jaccard(aff_sketch_b);
        double fmh_jaccard = fmh_sketch_a.jaccard(fmh_sketch_b);

        auto fmh_sketch_size_a = fmh_sketch_a.size();
        auto fmh_sketch_size_b = fmh_sketch_b.size();
        auto aff_sketch_size_a = aff_sketch_a.size();
        auto aff_sketch_size_b = aff_sketch_b.size();

        cout << size_a << "\t" << size_b << "\t" << fmh_sketch_size_a << "\t" << fmh_sketch_size_b << "\t" << aff_sketch_size_a << "\t" << aff_sketch_size_b << "\t" << true_jaccard << "\t" << aff_jaccard << "\t" << fmh_jaccard << endl;

    }

    return 0;
}