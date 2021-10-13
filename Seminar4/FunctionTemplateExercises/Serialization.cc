#include <istream>
#include <iostream>
#include <sstream>
#include <iostream>

using namespace std;

struct Product
{
    string name;
    double price;
    int inventory;
};

ostream& operator<<(ostream& os, Product const& product)
{
    return os << product.name << ": "
              << product.price << " kr ("
              << product.inventory << " available)";
}

template <typename T>
T read(istream& is)
{
    T data;
    is >> data;
    return data;
}

template <>
string read(istream& is) {
	string s{};
	is.ignore(numeric_limits<streamsize>::max(), '#');
	getline(is, s, '#');
	return s;	
}


template <>
Product read(istream& is)
{
	struct Product product;
	product.name = read<string>(is);	
	product.price = read<double>(is);	
	product.inventory = read<int>(is);	
	return product;
}

template <typename T>
void write(ostream& os, T const& t)
{
    os << t << ' ';
}

template <>
void write(ostream& os, string const& s) {
	os << '#' << s << '#' << ' ';
}

template <>
void write(ostream& os, Product const& p) {
	write(os, p.name);
	write(os, p.price);
	write(os, p.inventory);
}

int main()
{
    stringstream ss;
    { // send data to ss
        Product apple{"Red Apple", 1.5, 100};
        Product laptop{"Laptop", 5995.0, 10};
        Product monitor{"4K Monitor", 8790.0, 1};
        write(ss, apple);
        write(ss, laptop);
        write(ss, monitor);
    }

	cout << ss.str();
	cout << endl;

    { // recieve data from ss
        Product apple{read<Product>(ss)};
		cout << ss.str();
		cout << endl;
        Product laptop{read<Product>(ss)};
		cout << ss.str();
		cout << endl;
        Product monitor{read<Product>(ss)};
		cout << ss.str();
		cout << endl;
        cout << apple << endl
             << laptop << endl
             << monitor << endl;
    }
}

