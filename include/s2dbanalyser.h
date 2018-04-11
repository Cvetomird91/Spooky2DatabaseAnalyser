#ifndef S2DBANALYSER_H
#define S2DBANALYSER_H

#include <string>

#include <boost/date_time/gregorian/gregorian.hpp>


//utilities class with static method members
class s2dbanalyser
{
    public:
        static boost::gregorian::date generate_date(const std::string &filename);

};

#endif // S2DBANALYSER_H
