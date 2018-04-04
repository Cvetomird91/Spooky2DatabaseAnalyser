#include "Spooky2DatabaseAnalyser.h"

#include <string>
#include <vector>

#include <boost/filesystem.hpp>


Spooky2DatabaseAnalyser::Spooky2DatabaseAnalyser() {}

void Spooky2DatabaseAnalyser::setTxtFiles(boost::filesystem::path p) {

}

Spooky2DatabaseAnalyser::Spooky2DatabaseAnalyser(std::string path, std::string search_string) : m_Path(path),  m_Search_string(search_string) {
    this->setTxtFiles(m_Path);
}
