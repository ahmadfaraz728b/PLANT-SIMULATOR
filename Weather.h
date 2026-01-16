#ifndef WEATHER_H
#define WEATHER_H

#include <string>
using namespace std;

class Weather
{
public:
    string forecast();
    string today();
    string triggerEvent(int randomVal);
    string getForecast();
};

#endif
