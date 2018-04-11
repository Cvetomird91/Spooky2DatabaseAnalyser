#include "s2dbanalyser.h"

#include <string>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

//utilities class with static method members

std::string s2dbanalyser::generate_date(std::string filename) {
    boost::regex date(R"((\d{2})\.(\d{2})\.(\d{4}))");

    boost::smatch match;
    boost::gregorian::date d;
    std::ostringstream ss;

    if (boost::regex_search(filename, match, date)) {
        d = boost::gregorian::date(std::stoi(match[3]), std::stoi(match[2]), std::stoi(match[1]));
        ss << d.day() << ' ' << d.month() << ' ' << d.year();
    }

    return ss.str();
}
