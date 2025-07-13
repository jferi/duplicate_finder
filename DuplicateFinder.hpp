#pragma once
#include <string>
#include <vector>
#include <map>

struct Segment {
    std::string street;
    char scheme;
    int from;
    int to;
};

struct Interval {
    int from;
    int to;
};

using StreetKey = std::pair<std::string,char>;

class DuplicateFinder {
public:
    void addSegment(const Segment& s);
    void printDuplicates(std::ostream& out) const;
private:
    std::map<StreetKey, std::vector<Interval>> data_;
    static std::vector<Interval> findOverlaps(std::vector<Interval>& ivals);
};
