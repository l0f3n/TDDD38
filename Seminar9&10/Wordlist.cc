#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    // Add input to vector
    vector<string> text{istream_iterator<string>{cin}, istream_iterator<string>{}};
    vector<string> words{text};

    // Sort vector and keep only unique elements
    sort(begin(words), end(words));
    words.erase(unique(begin(words), end(words)), end(words));

    // Count the occurences of each word
    transform(begin(words), end(words), ostream_iterator<string>{cout, "\n"},
        [&text](string const& word)
        {
            int word_count{count(begin(text), end(text), word)};
            return word + ": " + to_string(word_count);
        });
}