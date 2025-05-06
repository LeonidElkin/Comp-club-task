#include "utils.h"

#include <chrono>
#include <iostream>
#include "CompClub.h"

std::chrono::minutes parseTimeToMinutes(const std::string &timeStr) {
	int hours = 0;
	int minutes = 0;
	char colon = 0;
	std::istringstream iss(timeStr);
	if (!(iss >> hours >> colon >> minutes) || colon != ':' || hours < 0 || hours >= max_hour || minutes < 0 ||
	    minutes >= max_minutes) {
		throw std::invalid_argument("Invalid time format: " + timeStr);
	}
	return std::chrono::hours(hours) + std::chrono::minutes(minutes);
};

CompClub parseAndValidateCompClubInfo(std::ifstream &input) {
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

	try {
		stTimeMinutes = parseTimeToMinutes(stTimeStr);
		endTimeMinutes = parseTimeToMinutes(endTimeStr);
	} catch (const std::invalid_argument &) {
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