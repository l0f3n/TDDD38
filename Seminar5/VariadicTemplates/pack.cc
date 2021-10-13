#include <string>
#include <type_traits>
#include <iostream>

template <typename T1, typename T2>
struct is_same {
	static bool const value{false};
};

template <typename T>
struct is_same<T, T> {
	static bool const value{true};
};


template <typename... Ts>
class Pack { };

namespace recursive {

	// ==== Contains

	// Base case 
	template <typename T>
		bool contains_helper(Pack<>) {
			return false;
		}

	// Helper 
	template <typename T, typename First, typename... Rest>
		bool contains_helper(Pack<First, Rest...>) {
			Pack<Rest...> rest;
			return std::is_same_v<T, First> || contains_helper<T>(rest);	
		}

	// Wrapper
	template <typename T, typename... Us>
		bool contains(Pack<Us...> p) {
			return contains_helper<T>(p);
		}

	// ==== Index of

	// Base case
	template <typename T>
		int index_of_helper(Pack<>, int) {
			return -1;
		}

	// Helper
	template <typename T, typename First, typename... Rest>
		int index_of_helper(Pack<First, Rest...>, int index = 0) {
			if (std::is_same_v<T, First>) {
				return index;
			} else {
				Pack<Rest...> rest;
				return index_of_helper<T>(rest, index+1);
			}
		}

	// Wrapper
	template <typename T, typename... Ts>
		int index_of(Pack<Ts...> p) {
			return index_of_helper<T>(p);
		}
}

inline namespace fold {
	
	template <typename T, typename... Ts>
	bool contains(Pack<Ts...>) {
		return (std::is_same_v<T, Ts> || ...);
	}

	template <typename T, typename... Ts>
	int index_of(Pack<Ts...>) {
		int index = -1;
		if (((index++, std::is_same_v<T, Ts>) || ...))
			return index;
		return -1;	
	}
}

int main()
{
	using std::cout;
	using std::endl;
	Pack<int, double, long, float, std::string> p{};

	cout << contains<long>(p) << endl;
	cout << contains<char>(p) << endl;
	cout << endl;
	cout << index_of<int>(p) << endl;
	cout << index_of<float>(p) << endl;
	cout << index_of<char>(p) << endl;
}
