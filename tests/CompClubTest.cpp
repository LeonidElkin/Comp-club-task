#include <gtest/gtest.h>

#include <chrono>
#include <filesystem>
#include <fstream>
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

static void execValid(int testNumber) {
	std::string basePath = PROJECT_SOURCE_DIR;
	std::string prefix = basePath + "/tests/input_files/";
	std::string testNumberStr = std::to_string(testNumber);
	std::string inputPath = prefix + "input" + testNumberStr + ".txt";
	std::string outputPath = prefix + "output" + testNumberStr + ".txt";
	std::string answerPath = prefix + "answer" + testNumberStr + ".txt";

	std::ifstream input(inputPath);
	std::ofstream output(outputPath);
	auto club = parseAndValidateCompClubInfo(input);
	club.parseEventsAndValidate(input);
	club.handleEvents();
	club.printResults(output);
	output.close();

	CompareFiles(outputPath, answerPath);
	std::filesystem::remove(outputPath);
}

class CompClubValidTest : public ::testing::TestWithParam<int> {};

TEST_P(CompClubValidTest, RunsCorrectly) {
	int testNumber = GetParam();
	execValid(testNumber);
}

INSTANTIATE_TEST_SUITE_P(DifferentScenarios, CompClubValidTest, ::testing::Values(1, 2, 3, 4, 8));

static void execInvalid(int testNumber) {
	std::string basePath = PROJECT_SOURCE_DIR;
	std::string prefix = basePath + "/tests/input_files/";
	std::string testNumberStr = std::to_string(testNumber);
	std::string inputPath = prefix + "input" + testNumberStr + ".txt";
	std::string answerPath = prefix + "answer" + testNumberStr + ".txt";
	std::ifstream input(inputPath);
	std::ifstream answerStream(answerPath);

	std::string ans;

	std::getline(answerStream, ans);

	try {
		auto club = parseAndValidateCompClubInfo(input);
		club.parseEventsAndValidate(input);
		FAIL();
	} catch (const std::runtime_error& e) {
		EXPECT_EQ(std::string(e.what()), ans);
	} catch (...) {
		FAIL();
	}
}

class CompClubInvalidInfoTest : public ::testing::TestWithParam<int> {};

TEST_P(CompClubInvalidInfoTest, RunsIncorrectly) {
	int testNumber = GetParam();
	execInvalid(testNumber);
}

INSTANTIATE_TEST_SUITE_P(DifferentIncorrectScenarios, CompClubInvalidInfoTest, ::testing::Values(5, 6, 7));

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