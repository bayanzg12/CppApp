#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <string>

class WeatherData {
public:
    WeatherData(); // Default constructor
    WeatherData(const std::string& desc, float temp, float feelsLike, float hum, float windSpeed, float minTemp, float maxTemp); // Parameterized constructor

    // Getters
    std::string getDescription() const;
    float getTemperature() const;
    float getFeelsLike() const;
    float getHumidity() const;
    float getWindSpeed() const;
    float getMinTemperature() const; // Getter for min temperature
    float getMaxTemperature() const; // Getter for max temperature

private:
    std::string description; // Weather description
    float temperature;       // Temperature in degrees
    float feelsLike;        // Feels-like temperature
    float humidity;         // Humidity percentage
    float windSpeed;        // Wind speed in units (e.g., km/h or mph)
    float minTemperature;   // Minimum temperature
    float maxTemperature;   // Maximum temperature
};

#endif // WEATHERDATA_H
