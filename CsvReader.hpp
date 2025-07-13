#include <fstream>
#include <string>
#include "DuplicateFinder.hpp"


class CsvReader {
    std::ifstream file_;
    Segment seg_;
    public:
        CsvReader(const std::string& filename);
        ~CsvReader();
        bool readRow(Segment& seg);
        std::string nextCsvField(std::istream& in);
};