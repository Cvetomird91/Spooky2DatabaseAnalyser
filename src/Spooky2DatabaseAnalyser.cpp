#include "Spooky2DatabaseAnalyser.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/regex.h>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace boost::filesystem;

Spooky2DatabaseAnalyser::Spooky2DatabaseAnalyser() {}

Spooky2DatabaseAnalyser::Spooky2DatabaseAnalyser(const boost::filesystem::path &path, const std::string &search_string) : m_Path(path),  m_Search_string(search_string) {
    this->frequency_line = boost::regex(R"(^Matches found for (\d{1,}).*?(?= \())");
    this->txt_filter = boost::regex(".*\.txt$");
    this->setTxtFiles(m_Path);
    this->results_container = new std::map <std::string, std::map<std::string, std::string> >();
    this->m_mor_rates = new std::set<std::string>();
    this->m_db_occurence_count = 0;
    this->occurence_dates = new std::vector<boost::gregorian::date>();
}

Spooky2DatabaseAnalyser::Spooky2DatabaseAnalyser(const std::string &path, const std::string &search_string)  {
    boost::filesystem::path boost_path = boost::filesystem::path(path);
    Spooky2DatabaseAnalyser(boost_path, search_string);
}

void Spooky2DatabaseAnalyser::setTxtFiles(const boost::filesystem::path &p) {
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
    for (unsigned int i = 0; i < this->txt_files.size(); i++) {
        std::ifstream *file = new std::ifstream(txt_files[i].string());
        std::set<std::string> *frequency_data_lines = new std::set<std::string>;
        std::string current_frequency_line;

        //generate the regex for matching the full pathogen names and octaves
        //e.g. abdominal.*\(octave #\d\)
        boost::regex full_name_octave(std::string(this->m_Search_string).append(".*?\\(octave #(\\d{1,}?)\\)"), boost::regex_constants::perl | boost::regex::icase);

        if (*file) {

            std::string *content = new std::string((std::istreambuf_iterator<char>(*file)), std::istreambuf_iterator<char>());
            boost::iterator_range<std::string::const_iterator> search_range_iterator = boost::ifind_first(*content, this->m_Search_string);

            delete content;

            if (search_range_iterator) {
                m_db_occurence_count++;
                (*results_container)[this->txt_files[i].string()];
                this->occurence_dates->push_back(s2dbanalyser::generate_date(this->txt_files[i].string()));
            } else {
                delete file;
                delete frequency_data_lines;

                continue;
            }

            file->clear();
            file->seekg(0);

            for(std::string str; std::getline(*file, str);) {

                boost::smatch match;
                int current_frequency;

                if(boost::regex_search(str, match, frequency_line)) {
                    current_frequency_line = match[0];
                    current_frequency = std::stoi(match[1]);
                }

                boost::iterator_range<std::string::const_iterator> rng;
                rng = boost::ifind_first(str, m_Search_string);

                if(rng) {
                    frequency_data_lines->insert(current_frequency_line);
                    (*results_container)[this->txt_files[i].string()][current_frequency_line];
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

                        //get octave and calculate MOR frequency
                        int octave = std::stoi(match[1]);
                        int mor_rate = octave * current_frequency;
                        m_mor_rates->insert(std::to_string(mor_rate));

                        flags != boost::regex_constants::match_prev_avail;
                        flags != boost::regex_constants::match_not_bob;
                    }

                    (*results_container)[this->txt_files[i].string()][current_frequency_line] = boost::algorithm::join(matches, ", ");

                }

            }

        }

        if(!this->occurence_dates->empty())
            std::sort(this->occurence_dates->begin(), this->occurence_dates->end());

        delete file;
        delete frequency_data_lines;

    }
}

void Spooky2DatabaseAnalyser::outputResults() {

    std::stringstream *str_stream;
    str_stream = this->getResultsStream();

    std::cout << str_stream->str();
    delete str_stream;
}

//method to stream the output to a string stream
std::stringstream* Spooky2DatabaseAnalyser::getResultsStream() {

    std::stringstream* stream = new std::stringstream();

    if (this->results_container->empty()) {
        *stream << std::endl;
        *stream << "Results container is empty! Exiting."<< std::endl;
        *stream << std::endl;

        std::exit(1);
    }

    for (std::map <std::string, std::map<std::string, std::string> >::iterator it = results_container->begin(); it != results_container->end(); ++it) {
        *stream << it->first << std::endl;

        std::map<std::string, std::string> file_data = it->second;

        for (std::map<std::string, std::string>::iterator itr = file_data.begin(); itr != file_data.end(); ++itr) {
            *stream << itr->first << std::endl;
            *stream << itr->second << std::endl;
        }

        *stream << std::endl;

    }

    std::string total_mor_rates = boost::algorithm::join(*m_mor_rates, ", ");

    *stream << std::endl;
    *stream << "Number of databases, containing the match: " << this->m_db_occurence_count << std::endl;
    *stream << std::endl;

    *stream << std::endl;
    *stream << "MOR rates:" << total_mor_rates << std::endl;
    *stream << std::endl;

    for ( std::vector<boost::gregorian::date>::const_iterator it = this->occurence_dates->begin(); it != this->occurence_dates->end();  ++it ) {
        *stream << *it << std::endl;
    }

    return stream;
}

Spooky2DatabaseAnalyser::~Spooky2DatabaseAnalyser() {
    delete this->results_container;
    delete this->m_mor_rates;
    delete this->occurence_dates;
}
