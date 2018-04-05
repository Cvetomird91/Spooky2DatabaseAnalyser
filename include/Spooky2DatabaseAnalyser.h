#ifndef SPOOKY2DATABASEANALYSER_H
#define SPOOKY2DATABASEANALYSER_H

#include <string>
#include <vector>
#include <map>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

class Spooky2DatabaseAnalyser
{
    public:
        Spooky2DatabaseAnalyser();
        Spooky2DatabaseAnalyser(boost::filesystem::path, std::string);
        void setTxtFiles(boost::filesystem::path);
        ~Spooky2DatabaseAnalyser();
        boost::regex txt_filter;
        void outputResults();

    private:
        boost::filesystem::path m_Path;
        std::string m_Search_string;
        std::vector<boost::filesystem::path> txt_files;
        std::map <std::string, std::map<std::string, std::string> > *results_container;

};

#endif // SPOOKY2DATABASEANALYSER_H
