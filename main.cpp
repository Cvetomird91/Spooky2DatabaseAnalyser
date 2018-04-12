#include <iostream>
#include <iterator>
#include <string>

#include <boost/filesystem.hpp>

#include "Spooky2DatabaseAnalyser.h"

using namespace boost::filesystem;

int main(int argc, char* argv[]) {

    if (argc < 3) {
        s2dbanalyser::show_usage(argv[0]);
        return 1;
    }

    path p( argc > 1 ? argv[1] : ".");
    std::string search_string = argv[2];

    Spooky2DatabaseAnalyser *parser = new Spooky2DatabaseAnalyser(p, search_string);
    parser->gatherResults();
    parser->outputResults();

    delete parser;

    return 0;
}
