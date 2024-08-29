
#ifndef WEATHERAPP_H
#define WEATHERAPP_H

#include <string>
#include <unordered_map>
#include "CommonObject.h"

class WeatherApp {
public:
    WeatherApp(const std::string& apiKey); // Constructor to accept API key
    void fetchWeatherData(const std::string& country, CommonObjects& common); // Updated signature
    std::string getWeatherResult(const std::string& country) const;

private:
    std::string apiKey;
    std::unordered_map<std::string, WeatherData> weatherCache;
};

#endif // WEATHERAPP_H
