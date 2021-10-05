#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main() {
	std::ifstream input_file{"WordLength.cpp"};
	std::string input_line{};

	int word_count{0};
	int character_count{0};
	std::string shortest_word{};
	std::string longest_word{};

	while(std::getline(input_file, input_line)) {
		int i{0};
		while(true) {
			std::string temp_word{};
			// Store characters in a string until a whitespace is found 
			while(!isspace(input_line[i]) && i < input_line.size()){
				temp_word += input_line.at(i);
				i++;
			}

			i++;

			word_count++; 
			character_count += temp_word.size();

			if(shortest_word.empty() || temp_word.size() < shortest_word.size())
				shortest_word = temp_word;	

			if(temp_word.size() > longest_word.size())
				longest_word = temp_word;	

			if(i >= input_line.size()) 
				break;
		}

	}

	std::cout << "There are " << word_count << " words in the file" << std::endl;
	std::cout << "The shortest word was \"" << shortest_word << "\" with " << shortest_word.size() << " character(s)" << std::endl;
	std::cout << "The shortest word was \"" << longest_word << "\" with " << longest_word.size() << " character(s)" << std::endl;
	std::cout << std::setprecision(2) << std::fixed << "The average length was " << (float)character_count / (float)word_count << " character(s)" << std::endl;

	return 0;
}
