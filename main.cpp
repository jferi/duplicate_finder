#include <iostream>
#include "DuplicateFinder.hpp"
#include "CsvReader.hpp"



int main()  {
    CsvReader reader("network.csv");
    Segment seg;
    DuplicateFinder finder;
    while(reader.readRow(seg)) {
        finder.addSegment(seg);
    }
    finder.printDuplicates(std::cout);

    return 0;
}