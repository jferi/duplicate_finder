# Duplicate Finder – Overlapping House‑Number Range Detector

This lightweight C++17 console program scans a street network CSV for house‑number range collisions: two or more records that describe overlapping ranges on the same street side (odd, even, or mixed).

---

## How It Works

1. The CSV is parsed line‑by‑line into `StreetSegment` objects (see `DuplicateFinder.hpp`).
2. Segments are grouped by `(street_name, side)` and their numeric ranges are normalised.
3. A sweep‑line algorithm tests each group for intersecting ranges and writes a concise report to stdout.

---

## Quick Start

```bash
# build
g++ -std=c++20 -O2 -o duplicate-finder \
    ./*.cpp

# run
./duplicate-finder
```

---

## Output Format

Each problematic pair is printed as:

```
[Street Name]: [Scheme] [From] [To]
```

---

