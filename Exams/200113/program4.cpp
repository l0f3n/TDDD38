#include <cassert>
#include <vector>
#include <list>
#include <forward_list>
#include <type_traits>
#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <numeric>

template <typename Container>
class range
{
public:
    using value_type = typename Container::value_type;
    using iterator = typename Container::iterator;

    range(iterator const &first, iterator const &last) : first{first}, last{last} {};

    iterator begin()
    {
        return first;
    };

    iterator end()
    {
        return last;
    };

    int size() const
    {
        return std::distance(first, last);
    };

    // Should probably check that take/skip doesn't invalidate the iterators

    range take(int n)
    {
        return range<Container>(first, std::next(first, n));
    };

    range skip(int n)
    {
        return range<Container>(std::next(first, n), last);
    };

private:
    iterator first, last;
};

// @Solution simply used another template parameter here to get a function
// parameter here, but that doesn't seem safe? On the other hand specifying
// them like this isn't that great either
template <typename Container>
range<Container> &map(range<Container> &r, std::function<typename range<Container>::value_type(typename range<Container>::value_type)> op)
{
    std::transform(r.begin(), r.end(), r.begin(), op);
    return r;
}

template <typename Container>
range<Container> &filter(range<Container> &r, std::function<bool(typename range<Container>::value_type)> pred)
{
    typename range<Container>::iterator it{std::remove_if(r.begin(), r.end(), pred)};
    r = range<Container>{r.begin(), it};
    return r;
}

template <typename Container>
typename range<Container>::value_type reduce(range<Container> &r, typename range<Container>::value_type initial, std::function<typename range<Container>::value_type(typename range<Container>::value_type, typename range<Container>::value_type)> op)
{
    return std::reduce(r.begin(), r.end(), initial, op);
}

// We cant return a reference here since we are creating a new range and that
// is and rvalue, which can't be bound to lvalue reference
template <typename Container>
range<Container> make_range(Container &container)
{
    return range<Container>{begin(container), end(container)};
}

int main()
{
    { // test reduce, map, and filter
        std::list<int> v{1, 2, 3, 4, 5, 6};
        auto r{make_range(v)};

        assert(reduce(map(filter(r, [](int n)
                                 { return n % 2 == 0; }),
                          [](int n)
                          { return 2 * n; }),
                      0.0,
                      [](int n, int m)
                      { return n + m; }) == 18);
    }

    { // test size, filter and range-based for-loop
        std::vector<double> v{-2.6, 7.0, 1.3, 15.2};
        auto r{make_range(v)};

        assert(r.size() == 4);
        filter(r, [](double x)
               { return x < 0.0; });
        assert(r.size() == 3);

        int i{0};
        for (double x : r)
        {
            assert(x == v[i++]);
        }
    }

    { // test take and skip
        std::forward_list<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto r{make_range(v)};

        int n{0};
        for (int x : r.take(3))
        {
            assert(x == n++);
        }

        for (int x : r.skip(3))
        {
            assert(x == n++);
        }
    }
}
