#include "Spooky2DatabaseAnalyser.h"

#include <string>
#include <vector>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/regex.h>

using namespace boost::filesystem;

Spooky2DatabaseAnalyser::Spooky2DatabaseAnalyser() {}

Spooky2DatabaseAnalyser::Spooky2DatabaseAnalyser(boost::filesystem::path path, std::string search_string) : m_Path(path),  m_Search_string(search_string) {
    this->txt_filter = boost::regex(".*\.txt$");
    this->setTxtFiles(m_Path);
    this->results_container = new std::map <std::string, std::map<std::string, std::string> >();
}

void Spooky2DatabaseAnalyser::setTxtFiles(boost::filesystem::path p) {
    if (is_directory(p)) {
        std::vector<directory_entry> v;
        copy(directory_iterator(p), directory_iterator(), back_inserter(v));

        //create an array with all the .txt files
        for ( std::vector<directory_entry>::const_iterator it = v.begin(); it != v.end();  ++it )
        {
            if(!boost::filesystem::is_regular_file(it->status()))
                continue;

            boost::smatch watch;

            if(boost::regex_match(it->path().string(), watch, txt_filter)) {
                this->txt_files.push_back(it->path());
            }
        }
    }

}

void Spooky2DatabaseAnalyser::gatherResults() {

}

Spooky2DatabaseAnalyser::~Spooky2DatabaseAnalyser() {
    delete this->results_container;
}
