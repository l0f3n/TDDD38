#include <iostream>

using namespace std;

namespace fold {
	
	// Fold expression
	template<typename... Args>
		void print(Args... args) {
			((std::cout << args << " ") , ...);
			std::cout << std::endl;
		}
}

namespace recursive {

	// Base case
	void print_helper() {
		std::cout << std::endl;
	}

	// Helper 
	template <typename First, typename... Rest>
	void print_helper(First first, Rest... rest) {
		std::cout << first << " ";
		print_helper(rest...);
	}

	// Wrapper
	template <typename... Args>
	void print(Args... args) {
		print_helper(args...);
	}
}

struct X { };

ostream& operator<<(ostream& os, X const&)
{
	return os << "X";
}

int main()
{
	// should produce an empty line
	recursive::print();

	// should produce:
	// a 3.5 100 hello
	recursive::print('a', 3.5, 100, "hello");

	// should produce:
	// a b
	recursive::print('a', 'b');

	// should produce:
	// X Y Z
	recursive::print(X{}, "Y", "Z");
}

