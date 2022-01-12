#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

using namespace std;

int main()
{
    double const length{10.0};
    vector<double> road{};

    // Copy input stream to back_inserter(road) @Solution
    copy(istream_iterator<double>{cin},
         istream_iterator<double>{},
         back_inserter(road));

    vector<double> result(road);

    // Left rotate by one
    rotate(begin(road), next(begin(road)), end(road));

    // Calculate difference between each segment
    transform(begin(road), end(road), begin(result), begin(result),
              [length](double a, double b)
              {
                  return sqrt((a - b) * (a - b) + length * length);
              });

    // Copy result to output stream @Solution
    copy(begin(result), end(result), ostream_iterator<double>{cout, "m\n"});

    // Add everything in result together. Default behaviour of accumulate is addition
    double total{accumulate(begin(result), end(result), 0.0)};

    cout << "Total distance: " << total << " m" << endl;
}
