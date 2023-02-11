#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

namespace MC {
	std::vector< std::string >		 Words;
	std::vector < std::vector<std::string> > Probability;

	void ReadSource(const std::string& file_path) {
		std::ifstream sourceFile; // "source.txt"
		sourceFile.open(file_path);
	
		std::string line;
		while (std::getline(sourceFile, line)) {
			//std::cout << "[MC] - LINE: " << line << std::endl;

			std::string word;
			int count = 0;
			for (std::string::iterator it = line.begin(); it != line.end(); ++it) {
				if (*it == ' ' || it == --line.end()) {
					Words.push_back(word);
					word = "";
					count++;
				}
				else {
					word += *it;
				}
			}
		}
	}
	void ReadSource(const std::string& file_path, char delim) {
		std::ifstream sourceFile;
		sourceFile.open(file_path);

		std::string line;
		while (std::getline(sourceFile, line, delim)) {
			Words.push_back(line);
		}
	}

	void SetProbability() {
		int i = 0, j = 0;
		for (auto it = Words.begin(); it != (Words.end() - 2); ++it) {
			std::vector<std::string> tempvec = { *it, *(it + 1) };
			Probability.push_back(tempvec);
		}
	}

	void Generate(std::string& output, std::size_t size) {
		std::size_t size_counter = 0;
		std::srand( (unsigned)time(NULL) );
		std::string current;

		std::size_t startPos = rand() % Probability.size();
		output += Probability[startPos][0];
		current = Probability[startPos][1];
		size_counter++;

		while (size_counter <= size) {
			std::vector<std::string> variants;
			for (std::size_t i = 0; i < Probability.size(); ++i) {
				if (Probability[i][0] == current) {
					variants.push_back(Probability[i][1]);
				}
			}

			output += " " + current;
			size_counter++;
			current = variants[rand() % variants.size()];
			variants.clear(); //TEST
		}

	}
}