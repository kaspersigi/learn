#include "WeatherStation.h"
#include <print>

auto main(int argc, char* argv[]) -> int
{
    WeatherData weatherData;
    CurrentConditionsDisplay currentDisplay(&weatherData);
    StatisticsDisplay statisticsDisplay(&weatherData);
    ForecastDisplay forecastDisplay(&weatherData);
    HeatIndexDisplay heatIndexDisplay(&weatherData);

    weatherData.setMeasurements(80, 65, 30.4f);
    std::println("--------------------");
    weatherData.setMeasurements(82, 70, 29.2f);
    std::println("--------------------");
    weatherData.setMeasurements(78, 90, 29.2f);

    return 0;
}