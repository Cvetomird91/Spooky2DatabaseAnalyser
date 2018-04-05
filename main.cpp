#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <chrono>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/regex.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "DatePatterns.h"
#include "Spooky2DatabaseAnalyser.h"

using namespace boost::filesystem;
using namespace boost::gregorian;
using namespace std::chrono;

const boost::regex txt_filter(".*\.txt$");
const boost::regex date_filter("[\d\.]{4,}");
const boost::regex frequency_line(R"(^Matches found.*?(?= \())");

int db_occurence_count = 0;

void show_usage(std::string name) {
    std::cerr << "Usage: " << name << " <path> <search-string>\n" << std::endl;
}

void show_result(std::vector<path> p) {

}

std::vector<std::string> get_dates();

int main(int argc, char* argv[]) {

    if (argc < 3) {
        show_usage(argv[0]);
        return 1;
    }

    path p( argc > 1 ? argv[1] : ".");
    std::string search_string = argv[2];
    std::vector<directory_entry> v; // To save all the .txt file names in a vector.
    std::vector<path> matching_files;
    std::map <std::string, std::map<std::string, std::string> > *results_container = new std::map <std::string, std::map<std::string, std::string> >();

    //generate the output filename

    Spooky2DatabaseAnalyser *parser = new Spooky2DatabaseAnalyser(p, search_string);
    parser->gatherResults();
    parser->outputResults();

    delete parser;

    return 0;
}
