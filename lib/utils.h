#pragma once

#include <chrono>

constexpr auto max_hour = 24;
constexpr auto max_minutes = 60;

std::chrono::minutes parseTimeToMinutes(const std::string &timeStr);