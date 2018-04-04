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
    system_clock::time_point point = system_clock::now();
    auto current_time = system_clock::to_time_t(point);
    std::cout << std::ctime(&current_time) << std::endl;

    std::ofstream *output_file = new std::ofstream();

    if(is_directory(p)) {
        copy(directory_iterator(p), directory_iterator(), back_inserter(v));

        //create an array with all the .txt files
        for ( std::vector<directory_entry>::const_iterator it = v.begin(); it != v.end();  ++it )
        {
            if(!boost::filesystem::is_regular_file(it->status()))
                continue;

            boost::smatch watch;

            if(boost::regex_match(it->path().string(), watch, txt_filter)) {
                matching_files.push_back(it->path());
            }
        }

        for (unsigned int i = 0; i < matching_files.size(); i++) {
            std::ifstream *file = new std::ifstream(matching_files[i].string());
            std::set<std::string> *frequency_data_lines = new std::set<std::string>;
            std::string current_frequency_line;

            //generate the regex for matching the full pathogen names and octaves
            //e.g. abdominal .*\(octave #\d\)
            boost::regex full_name_octave(std::string(search_string).append(".*?\\(octave #(\\d{1,}?)\\)"), boost::regex_constants::perl | boost::regex::icase);

            if (*file) {

                std::string *content = new std::string((std::istreambuf_iterator<char>(*file)), std::istreambuf_iterator<char>());
                boost::iterator_range<std::string::const_iterator> search_range_iterator = boost::ifind_first(*content, search_string);

                delete content;

                if (search_range_iterator) {
                    db_occurence_count++;
                    (*results_container)[matching_files[i].string()];
                } else {
                    delete file;
                    delete frequency_data_lines;

                    continue;
                }

                file->clear();
                file->seekg(0);

                for (std::string str; std::getline(*file, str);) {

                    boost::smatch match;

                    if(boost::regex_search(str, match, frequency_line)) {
                        current_frequency_line = match[0];
                    }

                    boost::iterator_range<std::string::const_iterator> rng;
                    rng = boost::ifind_first(str, search_string);

                    if(rng) {
                        frequency_data_lines->insert(current_frequency_line);
                        (*results_container)[matching_files[i].string()][current_frequency_line];
                    }

                    boost::smatch octave_match;

                    if(boost::regex_search(str, octave_match, full_name_octave)) {

                        std::string line(str);
                        std::string::const_iterator start = line.begin();
                        std::string::const_iterator end = line.end();

                        boost::regex_constants::match_flag_type flags = boost::match_default;
                        boost::smatch match;

                        std::set <std::string> matches;

                        while (start < end && boost::regex_search(start, end, match, full_name_octave, flags)) {
                            start += 1;

                            matches.insert(match[0]);

                            flags != boost::regex_constants::match_prev_avail;
                            flags != boost::regex_constants::match_not_bob;
                        }

                        (*results_container)[matching_files[i].string()][current_frequency_line] = boost::algorithm::join(matches, ", ");

                    }

                }

                delete file;
                delete frequency_data_lines;
            }

        }

    }

    for (std::map <std::string, std::map<std::string, std::string> >::iterator it = results_container->begin(); it != results_container->end(); ++it) {
        std::cout << it->first << std::endl;

        std::map<std::string, std::string> file_data = it->second;

        for (std::map<std::string, std::string>::iterator itr = file_data.begin(); itr != file_data.end(); ++itr) {
            std::cout << itr->first << std::endl;
            std::cout << itr->second << std::endl;
        }

        std::cout << std::endl;

    }


    std::cout << std::endl;
    std::cout << "Number of databases, containing the match: " << db_occurence_count << std::endl;
    std::cout << std::endl;

    delete results_container;
    delete output_file;

    Spooky2DatabaseAnalyser *parser = new Spooky2DatabaseAnalyser(path, "asd");

    return 0;
}
