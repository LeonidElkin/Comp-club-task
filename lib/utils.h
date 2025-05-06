#pragma once

#include <chrono>

#include "CompClub.h"

constexpr auto max_hour = 24;
constexpr auto max_minutes = 60;

std::chrono::minutes parseTimeToMinutes(const std::string &timeStr);
CompClub parseAndValidateCompClubInfo(std::ifstream &input);