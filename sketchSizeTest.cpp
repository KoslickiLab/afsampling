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
};


typedef Arguments Arguments;

Arguments arguments;


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

}



int main(int argc, char* argv[]) {
    
    parse_arguments(argc, argv);

    // show arguments from the global struct
    cout << "Scaled: " << arguments.scaled << endl;
    cout << "k: " << arguments.k << endl;

    return 0;
}