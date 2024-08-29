#include "WeatherData.h"

// Default constructor
WeatherData::WeatherData()
    : description(""), temperature(0.0f), feelsLike(0.0f), humidity(0.0f), windSpeed(0.0f), minTemperature(0.0f), maxTemperature(0.0f) {
}

// Constructor with parameters
WeatherData::WeatherData(const std::string& desc, float temp, float feelsLike, float hum, float windSpeed, float minTemp, float maxTemp)
    : description(desc), temperature(temp), feelsLike(feelsLike), humidity(hum), windSpeed(windSpeed), minTemperature(minTemp), maxTemperature(maxTemp) {}

// Getter implementations
std::string WeatherData::getDescription() const {
    return description;
}

float WeatherData::getTemperature() const {
    return temperature;
}

float WeatherData::getFeelsLike() const {
    return feelsLike;
}

float WeatherData::getHumidity() const {
    return humidity;
}

float WeatherData::getWindSpeed() const {
    return windSpeed;
}

float WeatherData::getMinTemperature() const {
    return minTemperature;
}

float WeatherData::getMaxTemperature() const {
    return maxTemperature;
}
