#include <cassert>
#include <utility> // std::forward lives in here :)

// Shorter names like F, Fs, f, fs (like @Solution) looks a lot cleaner

template <typename... Funcs>
class call_chain_result;

template <typename Func, typename... Funcs>
// We need to remember to put Func and Funcs... below here to actually make it
// a specialisation of the class defined above
class call_chain_result<Func, Funcs...>
{
public:
    call_chain_result(Func func, Funcs... funcs) : func{func}, rest{funcs...} {};

    template <typename... Args>
    // When using the rvalue reference syntax (&&) here, it actually becomes
    // a forwarding reference instead, which we need to do if we want to get
    // the correct reference types for the parameters
    auto operator()(Args &&...args)
    {
        // We use forward here to keep the correct reference types. The name
        // comes from the fact that it *forwards* the arguments to the next
        // function, so it can also be used to remember where to put it.
        // @Solution
        return rest(func(std::forward<Args>(args)...));
    }

private:
    Func func;
    call_chain_result<Funcs...> rest;
};

template <typename Func>
class call_chain_result<Func>
{
public:
    call_chain_result(Func func) : f{func} {};

    template <typename... Args>
    auto operator()(Args &&...args)
    {
        return f(std::forward<Args>(args)...);
    }

private:
    Func f;
};

template <typename... Funcs>
call_chain_result<Funcs...> call_chain(Funcs... funcs)
{
    return call_chain_result<Funcs...>{funcs...};
}

int start(int x, int y)
{
    return x + y;
}

double step(int x)
{
    return 0.5 * x;
}

int last(double x)
{
    return x;
}

int main()
{
    {
        int x{};
        auto f = call_chain(start, step, last);
        assert(f(x, x) == 0);

        x = 1;

        assert(f(x, x) == 1);

        assert(f(1, 4) == 2);
        assert(f(3, 3) == 3);
    }

    {
        auto f = call_chain([](int x = 1, int y = 1, int z = 1)
                            { return x * (y + z); },
                            [](int x)
                            { return x * x; },
                            [](int x)
                            { return x - 1; });

        assert(f() == 3);
        assert(f(2) == 15);
        assert(f(2, 3) == 63);
        assert(f(2, 3, 4) == 195);
    }

    {
        auto f = call_chain(call_chain([]()
                                       { return 1; },
                                       [](int x)
                                       { return x + 1; }),
                            [](int x)
                            { return x * x; });

        assert(f() == 4);
    }
}
