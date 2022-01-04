#include <iostream>
#include <algorithm>
#include <numeric>

int main() 
{
    int n;
    std::cin >> n;
    std::vector<unsigned long long int> fib(std::max(n, 2));
    std::fill_n(std::begin(fib), 2, 1);
    std::transform(std::begin(fib), std::end(fib)-2, std::begin(fib)+1, std::begin(fib)+2, [] (unsigned long long int a, unsigned long long int b) {
        return a+b;
    });

    std::cout << "Fibonacci(" << n << ")=" << fib[fib.size()-1] << std::endl;
}