#include "src/alphaAffirmativeSketch.h"
#include "argparse/argparse.hpp"
#include "mmh3/MurMurHash3.h"

#include <iostream>

using namespace std;

struct Args {
    double alpha;
    int num_elements;
};

struct Args args;

void parse_args(int argc, char **argv) {
    argparse::ArgumentParser program("alphaAffirmativeTest");

    program.add_argument("-a", "--alpha")
        .help("alpha value for the sketch")
        .required()
        .action([](const string &value) { args.alpha = stod(value); });

    program.add_argument("-n", "--num_elements")
        .help("number of elements to add to the sketch")
        .required()
        .action([](const string &value) { args.num_elements = stoi(value); });

    try {
        program.parse_args(argc, argv);
    } catch (const runtime_error &err) {
        cout << err.what() << endl;
        cout << program;
        exit(0);
    }
}

int main(int argc, char **argv) {
    parse_args(argc, argv);

    AlphaAffirmativeSketch sketch(args.alpha);

    // print the arguments
    cout << "alpha: " << args.alpha << endl;
    cout << "num_elements: " << args.num_elements << endl;

    // add elements to the sketch
    for (int i = 0; i < args.num_elements; i++) {
        auto hash_value = mmh3(&i, sizeof(i), 0);
        sketch.add(hash_value);
        //cout << "Added: " << hash_value << endl;
        //sketch.print();
    }

    // show sketch size
    cout << "Sketch size: " << sketch.get().size() << endl;

    return 0;
}