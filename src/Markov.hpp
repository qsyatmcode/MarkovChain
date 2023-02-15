#pragma once

#include "utf8cpp/utf8.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

namespace MC {
	std::vector< std::string >		 Words;
	std::vector < std::vector<std::string> > Probability;

	// Fixing string encoding
	void FixUTF(std::string& str) {
		std::string temp;
		utf8::replace_invalid(begin(str), end(str), back_inserter(temp));
		str = temp;
	}

	// Reading the source file by phrases
	void ReadSourceBP(const std::string& file_path) {
		std::ifstream sourceFile; // "source.txt"
		sourceFile.open(file_path);
	
		int count = 0;
		std::string line;
		while (std::getline(sourceFile, line)) {

			std::string word;
			for (std::string::iterator it = line.begin(); it != line.end(); ++it) {
				if (*it == ' ') {
					count++;
				}
				if ((*it == ' ' && count % 2 == 0) || it == --line.end()) {
					if (*it != ' ') {
						word += tolower(*it); // UTF-8 TROUBLE
					}
					Words.push_back(word);
					word = "";
				}
				else {
					word += tolower(*it); // UTF-8 TROUBLE
				}
			}
		}
	}
	
	// Read source file
	void ReadSource(const std::string& file_path) {
		std::ifstream sourceFile;
		sourceFile.open(file_path);

		if (!sourceFile.is_open()) {
			std::cout << "Failed to open file" << std::endl;
			return;
		}

		std::string line;
		while (std::getline(sourceFile, line)) {

			std::string word;
			for (std::string::iterator it = line.begin(); it != line.end(); ++it) {
				if (*it == ' ') {
					Words.push_back(word);
					word = "";
				}
				else {
					word += tolower(*it); // UTF-8 TROUBLE
				}
			}
			Words.push_back(word);
		}
	}

	//Read source file
	void ReadSource(const std::string& file_path, char delim) {
		std::ifstream sourceFile;
		sourceFile.open(file_path);

		if (!sourceFile.is_open()) {
			std::cout << "Failed to open file" << std::endl;
		}

		std::string line;

		while (std::getline(sourceFile, line, '\n')) {
			std::stringstream words(line);
			while (std::getline(words, line, delim)) {
				Words.push_back(line);
			}
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
		std::srand( (unsigned)time(NULL) );
		std::string current;

		std::size_t startPos = rand() % Probability.size();
		output += Probability[startPos][0];
		current = Probability[startPos][1];

		std::size_t size_counter = 1;
		while (size_counter <= size) {

			std::vector<std::string> variants;
			for (std::size_t i = 0; i < Probability.size(); ++i) {
				if (Probability[i][0] == current) {
					variants.push_back(Probability[i][1]);
				}
			}

			output += " " + current;
			size_counter++;
			if (variants.size() <= 0) {
				return; // size_counter = size;
			}
			current = variants[rand() % variants.size()];
			variants.clear();
		}
	}
}