#include "DuplicateFinder.hpp"
#include <algorithm>
#include <iomanip>
#include <map>

void DuplicateFinder::addSegment(const Segment& s) {
    data_[{s.street, s.scheme}].push_back({s.from, s.to});
}

std::vector<Interval> DuplicateFinder::findOverlaps(std::vector<Interval>& v) {
    if (v.size() <= 1) {
        return {};
    }

    std::map<int, int> points;
    for (const auto& iv : v) {
        if (iv.from <= iv.to) {
            points[iv.from]++;
            points[iv.to + 1]--;
        }
    }

    if (points.empty()) {
        return {};
    }

    std::vector<Interval> duplicates;
    int count = 0;
    int start_of_duplicate_range = 0;

    for (auto const& [point, change] : points) {
        int old_count = count;
        count += change;

        if (old_count <= 1 && count > 1) {
            start_of_duplicate_range = point;
        } else if (old_count > 1 && count <= 1) {
            duplicates.push_back({start_of_duplicate_range, point - 1});
        }
    }
    return duplicates;
}

void DuplicateFinder::printDuplicates(std::ostream& out) const {
    for (const auto& [key, intervals] : data_) {
        auto ivals = intervals;
        auto dups  = findOverlaps(ivals);
        for (auto [f, t] : dups) {
            out << key.first << ": " << key.second << ' '
                << f << ' ' << t << '\n';
        }
    }
}
