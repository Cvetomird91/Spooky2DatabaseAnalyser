#ifndef SPOOKY2DATABASEANALYSER_H
#define SPOOKY2DATABASEANALYSER_H

#include <string>
#include <vector>
#include <map>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "s2dbanalyser.h"

class Spooky2DatabaseAnalyser
{
    public:
        Spooky2DatabaseAnalyser();
        Spooky2DatabaseAnalyser(const boost::filesystem::path &path, const std::string &search_string);
        void setTxtFiles(const boost::filesystem::path &p);
        ~Spooky2DatabaseAnalyser();
        boost::regex txt_filter;
        void gatherResults();
        void outputResults();
        boost::regex frequency_line;
        std::vector<boost::gregorian::date> *occurence_dates;

    private:
        boost::filesystem::path m_Path;
        std::string m_Search_string;
        std::vector<boost::filesystem::path> txt_files;
        std::map <std::string, std::map<std::string, std::string> > *results_container;
        int m_db_occurence_count;
        std::set<std::string> *m_mor_rates;

};

#endif // SPOOKY2DATABASEANALYSER_H
