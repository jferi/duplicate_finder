#include "CsvReader.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

CsvReader::CsvReader(const std::string& filename) : file_(filename) {
    if (!file_.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

CsvReader::~CsvReader() {
    file_.close();
}

bool CsvReader::readRow(Segment& seg) {
    std::string line;
    while (std::getline(file_, line)) {
        std::stringstream ss(line);

        for (int i = 0; i < 16; i++) {
            nextCsvField(ss);
        }
        std::string street_name_1 = nextCsvField(ss);
        std::string street_name_2 = nextCsvField(ss);

        nextCsvField(ss);
        nextCsvField(ss);

        std::string scheme_str = nextCsvField(ss);
        if (scheme_str.empty() || (scheme_str[0] != 'O' && scheme_str[0] != 'E' && scheme_str[0] != 'M')) {
            continue;
        }

        std::string from_str = nextCsvField(ss);
        std::string to_str = nextCsvField(ss);

        if (from_str.empty() || to_str.empty()) {
            continue;
        }

        try {
            seg.street = street_name_1;
            if (!street_name_2.empty()) {
                seg.street += " " + street_name_2;
            }
            seg.scheme = scheme_str[0];
            seg.from = std::stoi(from_str);
            seg.to = std::stoi(to_str);
            
            if (seg.from > seg.to) {
                std::swap(seg.from, seg.to);
            }
            return true;
        } catch (const std::invalid_argument& e) {
            continue;
        }
    }
    return false;
}

std::string CsvReader::nextCsvField(std::istream& in) {
    std::string field, tmp;
    char c = in.peek();
    if (c == '"') {
        in.get();
        std::getline(in, field, '"');
        in.get();
    } else {
        std::getline(in, field, ',');
    }
    return field;
}