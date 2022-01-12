#include <type_traits>
#include <cassert>
#include <string>

template <typename T1, typename T2>
class common_type
{
public:
    using type = std::remove_reference_t<decltype(true ? std::declval<T1>() : std::declval<T2>())>;
};

template <typename T>
class common_type<T, void>
{
public:
    using type = void;
};

template <typename T>
class common_type<void, T>
{
public:
    using type = void;
};

template <>
class common_type<void, void>
{
public:
    using type = void;
};

int main()
{
    // is_same_v is true if both types in the template-argument list are the same
    // and false otherwise.
    assert((std::is_same_v<
            common_type<int, int>::type,
            int>));

    assert((std::is_same_v<
            common_type<int const, int>::type,
            int const>));

    assert((std::is_same_v<
            common_type<int, double>::type,
            double>));

    assert((std::is_same_v<
            common_type<double, int>::type,
            double>));

    assert((std::is_same_v<
            common_type<std::string, char const *>::type,
            std::string>));

    assert((std::is_same_v<
            common_type<void, int>::type,
            void>));

    assert((std::is_same_v<
            common_type<double, void>::type,
            void>));

    assert((std::is_same_v<
            common_type<void, void>::type,
            void>));
}