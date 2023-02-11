#include "Markov.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	auto start = chrono::high_resolution_clock::now();

	MC::ReadSource("source.txt");
	MC::SetProbability();

	/*for (size_t i = 0; i < MC::Probability.size(); ++i) {
		for (size_t j = 0; j < MC::Probability[i].size(); ++j) {
			cout << MC::Probability[i][j] << ' ';
		}
		cout << endl;
	}*/

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds> (stop - start);
	cout << endl;
	cout << duration.count() << "ms" << endl;
	cout << endl;

	while (getchar()) {
		std::string output;

		MC::Generate(output, 100);

		cout << "> " << output << endl;
	}
}