
#include "DrawThread.h"
#include "GuiMain.h"
#include "../../shared/ImGuiSrc/imgui.h"
#include <ctime>
#include "DownloadThread.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

extern ImFont* custom_font;

// Function to get the current date as a string
std::string getCurrentDate() {
    time_t t = time(0); // Get current time
    struct tm now; // Declare a tm structure
    localtime_s(&now, &t); // Safe conversion to local time structure

    char buffer[100];
    strftime(buffer, sizeof(buffer), "%A, %B %d", &now);
    return std::string(buffer);
}

ImVec4 clear_color = ImVec4(0.8f, 0.7f, 0.9f, 1.0f); // Color
ImVec4 text_color = ImVec4(0.0f, 0.0f, 1.0f, 1.0f); // Default text color

// Function to convert Celsius to Fahrenheit
float CelsiusToFahrenheit(float celsius) {
    return (celsius * 9.0f / 5.0f) + 32.0f;
}

// Function to generate a random color
ImVec4 GetRandomColor() {
    return ImVec4(
        static_cast<float>(rand()) / RAND_MAX,
        static_cast<float>(rand()) / RAND_MAX,
        static_cast<float>(rand()) / RAND_MAX,
        1.0f
    );
}

// Draw the application window
void DrawAppWindow(void* common_ptr) {
    auto common = (CommonObjects*)common_ptr;
    static char countryInput[128] = ""; // Buffer for user input
    static bool showInFahrenheit = false; // Flag to toggle between Celsius and Fahrenheit

    ImGui::Begin("Weather Forecast");

    // Search Bar
    ImGui::InputText("Country", countryInput, IM_ARRAYSIZE(countryInput));

    // Search Button
    if (ImGui::Button("Search")) {
        // Trigger data fetching
        WeatherApp weatherApp("c9e845bc59bc9b42263a97c19ff602a7"); // API key needs to be handled appropriately
        weatherApp.fetchWeatherData(countryInput, *common);
       

        // Change the text color to a random color
        text_color = GetRandomColor();
    }

    ImGui::SameLine(); // Place next button on the same line

    // Fahrenheit Button
    if (ImGui::Button("Fahrenheit")) {
        showInFahrenheit = true; // Set to Fahrenheit
    }

    ImGui::SameLine(); // Place next button on the same line

    // Celsius Button
    if (ImGui::Button("Celsius")) {
        showInFahrenheit = false; // Set to Celsius
    }

    ImGui::SameLine(); // Place next button on the same line

    // Delete Button
    if (ImGui::Button("Delete")) {
        common->data_ready = false; // Clear the weather data
    }

    ImGui::Spacing(); // Add space between buttons and weather data

    // Display the error message if there is one
    if (!common->error_message.empty()) {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", common->error_message.c_str()); // Display error message in red
    }

    if (common->data_ready) {
        const WeatherData& weather = common->weatherData;

        ImGui::PushStyleColor(ImGuiCol_Text, text_color); // Set text color to the random color

        ImGui::Text("Location: %s", common->country.c_str());
        ImGui::Text("%s", getCurrentDate().c_str());
        ImGui::Separator();

        // Display temperature in the selected unit
        if (showInFahrenheit) {
            ImGui::Text("Description: %s", weather.getDescription().c_str());
            ImGui::Text("Temperature: %.1fF", CelsiusToFahrenheit(weather.getTemperature()));
            ImGui::Text("Feels Like: %.1fF", CelsiusToFahrenheit(weather.getFeelsLike()));
            ImGui::Text("Max: %.1fF, Min: %.1fF", CelsiusToFahrenheit(weather.getMaxTemperature()), CelsiusToFahrenheit(weather.getMinTemperature()));
        }
        else {
            ImGui::Text("Description: %s", weather.getDescription().c_str());
            ImGui::Text("Temperature: %.1fC", weather.getTemperature());
            ImGui::Text("Feels Like: %.1fC", weather.getFeelsLike());
            ImGui::Text("Max: %.1fC, Min: %.1fC", weather.getMaxTemperature(), weather.getMinTemperature());
        }

        ImGui::Separator();
        ImGui::Text("Humidity: %.1f%%", weather.getHumidity());
        ImGui::Text("Wind Speed: %.1f m/s", weather.getWindSpeed());

        ImGui::PopStyleColor(); // Restore default text color
    }
    else {
        ImGui::Text("");
    }

    ImGui::End();
}

// Operator() function for the DrawThread
void DrawThread::operator()(CommonObjects& common) {
    GuiMain(DrawAppWindow, &common);
    common.exit_flag = true;
}