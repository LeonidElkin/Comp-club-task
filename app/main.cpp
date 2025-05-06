#include <chrono>
#include <fstream>
#include <iostream>
#include <span>

#include "CompClub.h"
#include "utils.h"

int main(int argc, char **argv) {
	std::span const args(argv, argc);

	if (args.size() != 2) {
		std::cerr << "Usage: " << args[0] << " <input_file>\n";
		return 1;
	}

	std::ifstream inputFile(args[1]);
	if (inputFile.is_open()) {
		try {
			auto club = parseAndValidateCompClubInfo(inputFile);
			club.parseEventsAndValidate(inputFile);
			club.handleEvents();
			club.printResults(std::cout);
		} catch (std::runtime_error &e) {
			std::cout << e.what();
			return 1;
		}
	} else {
		std::cerr << "Couldn't open the input file " << args[1] << "\n";
		inputFile.close();
		return 1;
	}

	return 0;
}