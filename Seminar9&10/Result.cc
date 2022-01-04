#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <iomanip>

/* Expected output:

Highscore      | Fastest       
Team D  : 37   | Team C
Team C  : 12   | Team B
Team B  : 5    | Team A

*/

std::string team_to_string(std::pair<std::string, int> const& team)
{
    std::ostringstream oss{};
    oss << std::left << std::setw(8) << team.first
        << ": " << std::setw(4) << team.second;
    return oss.str();
}

int main()
{
    std::vector<std::pair<std::string, int>> const results {
        {"Team C", 12},
        {"Team B", 5},
        {"Team A", 0},
        {"Team D", 37},
    };

    std::vector<std::pair<std::string, int>> highscore{results};

    std::cout << std::left << std::setw(15) << "Highscore" << "| " << "Fastest" << std::endl;
    
    std::sort(std::begin(highscore), std::end(highscore), [] (std::pair<std::string, int> a, std::pair<std::string, int> b) {
        return a.second >= b.second;
    });

    std::transform(std::begin(highscore), std::end(highscore) - 1, std::begin(results), std::ostream_iterator<std::string>{std::cout, "\n"}, 
    [] (std::pair<std::string, int> a, std::pair<std::string, int> b) {
            return team_to_string(a) + " | " + b.first;
        }
    );

}