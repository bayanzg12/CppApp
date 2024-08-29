#include <httplib.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include "DownloadThread.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

// Constructor
WeatherApp::WeatherApp(const std::string& apiKey) : apiKey(apiKey) {}

void WeatherApp::fetchWeatherData(const std::string& country, CommonObjects& common) {
    httplib::Client cli("http://api.openweathermap.org");
    std::string apiPath = "/data/2.5/weather?q=" + country + "&appid=" + apiKey + "&units=metric";
    auto res = cli.Get(apiPath.c_str());

    if (res && res->status == 200) {
        try {
            auto jsonData = nlohmann::json::parse(res->body);
            std::string description = jsonData["weather"][0]["description"];
            float temperature = jsonData["main"]["temp"];
            float feelsLike = jsonData["main"]["feels_like"];
            float humidity = jsonData["main"]["humidity"];
            float windSpeed = jsonData["wind"]["speed"];
            float minTemperature = jsonData["main"]["temp_min"]; // Get min temperature
            float maxTemperature = jsonData["main"]["temp_max"]; // Get max temperature

            // Store fetched weather data
            weatherCache[country] = WeatherData(description, temperature, feelsLike, humidity, windSpeed, minTemperature, maxTemperature);
            common.weatherData = weatherCache[country]; // Update common weather data
            common.country = country; // Set the country name
            common.data_ready = true; // Set data ready flag
        }
        catch (const std::exception& e) {
            std::cerr << "JSON Parsing Error: " << e.what() << std::endl;
        }
    }
    else {
        std::cerr << "Failed to get weather data for " << country << ". Status code: " << (res ? res->status : 0) << std::endl;
    }
}

std::string WeatherApp::getWeatherResult(const std::string& country) const {
    if (weatherCache.find(country) != weatherCache.end()) {
        const WeatherData& data = weatherCache.at(country);
        return "Description: " + data.getDescription() +
            "\nTemperature: " + std::to_string(data.getTemperature()) + " °C" +
            "\nFeels Like: " + std::to_string(data.getFeelsLike()) + " °C" +
            "\nHumidity: " + std::to_string(data.getHumidity()) + " %" +
            "\nWind Speed: " + std::to_string(data.getWindSpeed()) + " m/s" +
            "\nMax: " + std::to_string(data.getMaxTemperature()) + " °C" +
            "\nMin: " + std::to_string(data.getMinTemperature()) + " °C";
    }
    return "No data available.";
}