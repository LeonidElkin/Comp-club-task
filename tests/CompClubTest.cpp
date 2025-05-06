#include <gtest/gtest.h>

#include <chrono>
#include <filesystem>
#include <string>

#include "utils.h"

static void CompareFiles(const std::string& file1, const std::string& file2) {
	std::ifstream f1(file1), f2(file2);
	ASSERT_TRUE(f1.is_open()) << "Cannot open file: " << file1;
	ASSERT_TRUE(f2.is_open()) << "Cannot open file: " << file2;

	std::string line1, line2;
	int line_num = 1;
	while (std::getline(f1, line1) && std::getline(f2, line2)) {
		ASSERT_EQ(line1, line2) << "Mismatch at line " << line_num;
		++line_num;
	}
}

TEST(CompClub, Integration) {
	std::string basePath = PROJECT_SOURCE_DIR;
	std::string inputPath = basePath + "/tests/input_files/input1.txt";
	std::string outputPath = basePath + "/tests/input_files/output1.txt";
	std::string answerPath = basePath + "/tests/input_files/answer1.txt";
	std::ifstream input(inputPath);
	std::ofstream output(outputPath);
	auto club = parseAndValidateCompClubInfo(input);
	club.parseEventsAndValidate(input);
	club.handleEvents();
	club.printResults(output);

	CompareFiles(outputPath, answerPath);

	output.close();
	std::filesystem::remove(outputPath);
}

TEST(utils, simpleCase) {
	std::string testString{"23:52"};
	std::chrono::minutes exp = std::chrono::hours(23) + std::chrono::minutes(52);
	auto ans = parseTimeToMinutes(testString);
	EXPECT_EQ(ans, exp);
}

TEST(utils, firstZeroParse) {
	std::string testString{"03:52"};
	std::chrono::minutes exp = std::chrono::hours(3) + std::chrono::minutes(52);
	auto ans = parseTimeToMinutes(testString);
	EXPECT_EQ(ans, exp);
}