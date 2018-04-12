#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <set>
#include <map>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/regex.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "Spooky2DatabaseAnalyser.h"

using namespace boost::filesystem;

void show_usage(std::string name) {
    std::cerr << "Usage: " << name << " <path> <search-string>\n" << std::endl;
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        show_usage(argv[0]);
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
