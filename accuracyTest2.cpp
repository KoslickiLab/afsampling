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
    int scaled;
    int num_trials;
    int size_low;
    int size_high;
    int max_size;
    vector<int> kValuesForAffirmativeSketch;
};

typedef Arguments Arguments;

Arguments arguments;


/*
This function parses the arguments, and sets the global struct arguments.
The plan is to make this struct available to all functions in the program.
*/
void parse_arguments(int argc, char* argv[]) {
    // Define the parser
    argparse::ArgumentParser program("accuracyTest2", "0.0.0");

    // Define the arguments
    // scaled
    program.add_argument("-s", "--scaled")
        .help("Scaled value for FracMinHashSketch")
        .scan<'i', int>()
        .default_value(1000);

    // number of trials in each setting
    program.add_argument("-n", "--num_trials")
        .help("Number of trials in each setting")
        .scan<'i', int>()
        .default_value(100);

    // size_low
    program.add_argument("-l", "--size_low")
        .help("Lowest size of the set")
        .scan<'i', int>()
        .default_value(100);

    // size_high
    program.add_argument("-H", "--size_high")
        .help("Highest size of the set")
        .scan<'i', int>()
        .default_value(1000);

    // max_size
    program.add_argument("-m", "--max_size")
        .help("Maximum size of the set")
        .scan<'i', int>()
        .default_value(10000);

    // k values
    program.add_argument("-k", "--k_values")
        .help("k values for AffirmativeSketch")
        .nargs(1,5)
        .default_value(std::vector<int>{100})
        .scan<'i', int>();
        
        
    // Parse the arguments
    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        exit(1);
    }

    // set the arguments in the global struct
    arguments.scaled = program.get<int>("--scaled");
    arguments.num_trials = program.get<int>("--num_trials");
    arguments.size_low = program.get<int>("--size_low");
    arguments.size_high = program.get<int>("--size_high");
    arguments.max_size = program.get<int>("--max_size");
    arguments.kValuesForAffirmativeSketch = program.get<vector<int>>("--k_values");


}


int main(int argc, char* argv[]) {
    // Parse the arguments
    parse_arguments(argc, argv);

    int size_a = arguments.size_high/2;
    vector<int> set_a;
    for (int i = 0; i < size_a; i++) {
        set_a.push_back( rand() % arguments.max_size );
    }

    // create the sketches for set a
    vector<AffirmativeSketch> aff_sketches_a = {};
    for (int k : arguments.kValuesForAffirmativeSketch) {
        AffirmativeSketch aff_sketch_a(k);
        aff_sketches_a.push_back(aff_sketch_a);
    }
    FracMinHashSketch fmh_sketch_a(arguments.scaled);
    Sketch no_subsampling_sketch_a;

    // add the elements to the sketches
    for (int element : set_a) {
        auto hash_value = mmh3(&element, sizeof(element), 0);
        fmh_sketch_a.add(hash_value);
        no_subsampling_sketch_a.add(hash_value);
        for (AffirmativeSketch& aff_sketch : aff_sketches_a) {
            aff_sketch.add(hash_value);
        }
    }


    for (int i = 0; i < arguments.num_trials; i++) {

        int size_b = rand() % (arguments.size_high - arguments.size_low) + arguments.size_low;
        vector<int> set_b;
        
        for (int i = 0; i < size_b; i++) {
            set_b.push_back( rand() % arguments.max_size );
        }

        // create the sketches for set b
        vector<AffirmativeSketch> aff_sketches_b = {};
        for (int k : arguments.kValuesForAffirmativeSketch) {
            AffirmativeSketch aff_sketch_b(k);
            aff_sketches_b.push_back(aff_sketch_b);
        }
        FracMinHashSketch fmh_sketch_b(arguments.scaled);
        Sketch no_subsampling_sketch_b;

        // add the elements to the sketches
        for (int element : set_b) {
            auto hash_value = mmh3(&element, sizeof(element), 0);
            fmh_sketch_b.add(hash_value);
            no_subsampling_sketch_b.add(hash_value);
            for (AffirmativeSketch& aff_sketch : aff_sketches_b) {
                aff_sketch.add(hash_value);
            }
        }


        double true_jaccard = no_subsampling_sketch_a.jaccard(no_subsampling_sketch_b);
        double fmh_jaccard = fmh_sketch_a.jaccard(fmh_sketch_b);
        vector<double> aff_jaccards = {};
        for (int i = 0; i < arguments.kValuesForAffirmativeSketch.size(); i++) {
            aff_jaccards.push_back(aff_sketches_a[i].jaccard(aff_sketches_b[i]));
        }

        cout << size_a << "\t" << size_b << "\t" << true_jaccard << "\t";
        for (double aff_jaccard : aff_jaccards) {
            cout << aff_jaccard << "\t";
        }
        cout << fmh_jaccard << endl;


    }



    return 0;
}