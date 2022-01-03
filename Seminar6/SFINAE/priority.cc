#include <utility>
#include <iostream>

template <typename T>
auto get_priority_helper(T&& t, int, int) -> decltype(t.first())
{
    return t.first();
}

template <typename T>
auto get_priority_helper(T&& t, long, int) -> decltype(t.second())
{
    return t.second();
}

template <typename T>
auto get_priority_helper(T&& t, long, long) -> decltype(t.third())
{
    return t.third();
}

int get_priority_helper(...)
{
    return 4;
}

template <typename T>
auto get_priority(T&& t)
{
  return get_priority_helper(std::forward<T>(t), 0, 0);
}

struct X
{
  int first() const { return 1; }
};

struct Y
{
  int second() const { return 2; }
};

struct Z
{
  int third() const { return 3; }
};

struct XY
{
  int first() const { return 1; }
  int second() const { return 2; }
};

struct XZ
{
  int first() const { return 1; }
  int third() const { return 3; }
};

struct YZ
{
  int second() const { return 2; }
  int third() const { return 3; }
};

struct XYZ
{
  int first() const { return 1; }
  int second() const { return 2; }
  int third() const { return 3; }
};

int main()
{
  using std::cout;
  using std::endl;
  
  cout << get_priority(X{}) << endl
       << get_priority(Y{}) << endl
       << get_priority(Z{}) << endl
       << get_priority(XY{}) << endl
       << get_priority(XZ{}) << endl
       << get_priority(YZ{}) << endl
       << get_priority(XYZ{}) << endl
       << get_priority(5) << endl;
}
