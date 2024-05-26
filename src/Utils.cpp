#include "Utils.hpp"
#include <iomanip>
#include <sstream>

std::chrono::system_clock::time_point stringToTimePoint(const std::string& date) {
    std::tm tm = {};
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::string timePointToString(const std::chrono::system_clock::time_point& tp) {
    std::time_t time = std::chrono::system_clock::to_time_t(tp);
    std::tm tm = *std::localtime(&time);
    char buffer[11]; // YYYY-MM-DD + null terminator
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
    return std::string(buffer);
}
