#include <chrono>
#include "utils.h"

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