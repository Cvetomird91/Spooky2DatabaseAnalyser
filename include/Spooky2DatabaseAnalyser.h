#ifndef SPOOKY2DATABASEANALYSER_H
#define SPOOKY2DATABASEANALYSER_H

#include <string>
#include <vector>

#include <boost/filesystem.hpp>

class Spooky2DatabaseAnalyser
{
    public:
        Spooky2DatabaseAnalyser();
        Spooky2DatabaseAnalyser(std::string, std::string);
        void setTxtFiles(boost::filesystem::path);

    private:
        std::string m_Path;
        std::string m_Search_string;
        std::vector<boost::filesystem::path> txt_files;

};

#endif // SPOOKY2DATABASEANALYSER_H
