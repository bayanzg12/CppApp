
#ifndef COMMONOBJECTS_H
#define COMMONOBJECTS_H

#include <vector>
#include <string>
#include "WeatherData.h" // Assuming WeatherData is defined in this file

struct CommonObjects{
    bool data_ready = false;
    WeatherData weatherData;
    std::string country;
    std::vector<std::string> favorites; // List of favorite locations
    bool exit_flag = false;
    std::string error_message; // To store error messages
};
#endif // COMMONOBJECTS_H
