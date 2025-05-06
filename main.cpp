#include <chrono>
#include <fstream>
#include <iostream>
#include <span>

struct CompClubInfo {
	size_t tablesNum{};
	size_t costPerHour{};
	std::chrono::hh_mm_ss<std::chrono::minutes> startTime;
	std::chrono::hh_mm_ss<std::chrono::minutes> endTime;
};

static std::optional<CompClubInfo> parseAndValidateFile(std::ifstream &input) {
	std::string lineOfInput;
	std::istringstream sInput;
	size_t tablessNum{0ULL};
	size_t costPerHour{0ULL};

	std::getline(input, lineOfInput);
	sInput.str(lineOfInput);

	if (!(sInput >> tablessNum)) {
		std::cerr << lineOfInput;
		return std::nullopt;
	}

	std::getline(input, lineOfInput);
	sInput.clear();
	sInput.str(lineOfInput);
	std::string stTimeStr;
	std::string endTimeStr;

	if (!(sInput >> stTimeStr >> endTimeStr)) {
		std::cerr << lineOfInput;
		return std::nullopt;
	}

	std::chrono::minutes stTimeMinutes;
	std::chrono::minutes endTimeMinutes;

	if (!(std::istringstream(stTimeStr) >> std::chrono::parse("%R", stTimeMinutes)) ||
	    !(std::istringstream(endTimeStr) >> std::chrono::parse("%R", endTimeMinutes))) {
		std::cerr << lineOfInput;
		return std::nullopt;
	}

	std::chrono::hh_mm_ss<std::chrono::minutes> const stHHMM{stTimeMinutes};
	std::chrono::hh_mm_ss<std::chrono::minutes> const endHHMM{endTimeMinutes};

	std::getline(input, lineOfInput);
	sInput.clear();
	sInput.str(lineOfInput);

	if (!(sInput >> costPerHour)) {
		std::cerr << lineOfInput;
		return std::nullopt;
	}

	return CompClubInfo{.tablesNum = tablessNum, .costPerHour = costPerHour, .startTime = stHHMM, .endTime = endHHMM};
}

int main(int argc, char **argv) {
	std::span const args(argv, argc);

	if (args.size() != 2) {
		std::cerr << "Usage: " << args[0] << " <input_file>\n";
		return 1;
	}

	std::ifstream inputFile(args[1]);
	if (inputFile.is_open()) {
		auto info = parseAndValidateFile(inputFile);
		if (info.has_value()) {
			auto i = *info;
			std::cout << info->startTime.to_duration() << " " << info->endTime.to_duration();
		} else {
			return 1;
		}
	} else {
		std::cerr << "Couldn't open the input file" << args[1] << "\n";
		inputFile.close();
		return 1;
	}

	return 0;
}