#include "WeatherStation.h"
#include <iostream>
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    auto weatherData = std::make_shared<WeatherData>();

    auto currentDisplay = std::make_shared<CurrentConditionsDisplay>(weatherData);
    weatherData->registerObserver(currentDisplay);

    auto statisticsDisplay = std::make_shared<StatisticsDisplay>(weatherData);
    weatherData->registerObserver(statisticsDisplay);

    auto forecastDisplay = std::make_shared<ForecastDisplay>(weatherData);
    weatherData->registerObserver(forecastDisplay);

    auto heatIndexDisplay = std::make_shared<HeatIndexDisplay>(weatherData);
    weatherData->registerObserver(heatIndexDisplay);

    weatherData->setMeasurements(80, 65, 30.4f);
    std::cout << "--------------------" << std::endl;
    weatherData->setMeasurements(82, 70, 29.2f);
    std::cout << "--------------------" << std::endl;
    weatherData->setMeasurements(78, 90, 29.2f);

    return 0;
}