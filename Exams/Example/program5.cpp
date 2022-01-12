#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>

using namespace std;

int rotate(vector<int> &denominators, int k)
{
    rotate(begin(denominators), next(begin(denominators), k + 1), end(denominators));

    // return how far in the overlap ends
    return denominators.size() - k;
}

int main()
{
    int n, k;
    std::cin >> n >> k;

    // store a vector of all factors in the numerator
    vector<int> factors(n - k, 0);

    // store a vector of all divisors in the denominator
    vector<int> denominators(n - k, 0);

    // fill factors with k+1, k+2, ..., n-1, n
    iota(begin(factors), end(factors), k + 1);

    // fill denominators with 1, 2, ..., n-k-1, n-k
    iota(begin(denominators), end(denominators), 1);

    // if there is overlap between factors and denominators we remove it
    if (denominators.size() > k)
    {
        // restructure denominators so that the overlap is in the
        // beginning of the vector and retrieve how many elements there
        // where in the overlap
        auto dist{rotate(denominators, k)};

        // remove the overlap
        factors.erase(factors.begin(), next(factors.begin(), dist));
        denominators.erase(denominators.begin(), next(denominators.begin(), dist));
    }

    int i{0};
    generate(
        begin(denominators), end(denominators), [&factors, &denominators, &i]()
        {
            // find a factor that is divisible by the current denominator
            vector<int>::iterator it = find_if(begin(factors), end(factors), [&denominators, &i](int value)
                                               { return value % denominators[i] == 0; });

            // divide the found factor
            *it /= denominators[i++];
            return 1;
        });

    // multiply all factors together
    int result{reduce(begin(factors), end(factors), 1, [](int a, int b)
                      { return a * b; })};

    // print the result
    cout << result << endl;
}
