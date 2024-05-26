#ifndef UTILS_HPP
#define UTILS_HPP

#include <chrono>
#include <string>

std::chrono::system_clock::time_point stringToTimePoint(const std::string& date);
std::string timePointToString(const std::chrono::system_clock::time_point& tp);

#endif
