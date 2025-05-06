#include <chrono>
#include <fstream>
#include <iostream>
#include <span>

#include "CompClub.h"

static CompClub parseAndValidateCompClubInfo(std::ifstream &input) {
	std::string lineOfInput;
	std::istringstream sInput;
	size_t tablesNum{0ULL};
	size_t costPerHour{0ULL};

	std::getline(input, lineOfInput);
	sInput.str(lineOfInput);

	if (!(sInput >> tablesNum)) {
		throw std::runtime_error(lineOfInput);
	}

	std::getline(input, lineOfInput);
	sInput.clear();
	sInput.str(lineOfInput);
	std::string stTimeStr;
	std::string endTimeStr;

	if (!(sInput >> stTimeStr >> endTimeStr)) {
		throw std::runtime_error(lineOfInput);
	}

	std::chrono::minutes stTimeMinutes;
	std::chrono::minutes endTimeMinutes;

	if (!(std::istringstream(stTimeStr) >> std::chrono::parse("%R", stTimeMinutes)) ||
	    !(std::istringstream(endTimeStr) >> std::chrono::parse("%R", endTimeMinutes))) {
		throw std::runtime_error(lineOfInput);
	}

	std::getline(input, lineOfInput);
	sInput.clear();
	sInput.str(lineOfInput);

	if (!(sInput >> costPerHour)) {
		throw std::runtime_error(lineOfInput);
	}

	return CompClub(tablesNum, costPerHour, stTimeMinutes, endTimeMinutes);
}

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