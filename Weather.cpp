#include "Weather.h"
#include <cstdlib>

string Weather::forecast()
{
    int r=rand()%3;
    if(r==0) return "🌞 Sunny";
    if(r==1) return "🌧️ Rain";
    return "🌫️ Normal";
}

string Weather::today()
{
    int r=rand()%100;
    if(r<25) return "Rain";
    if(r<45) return "Sunny";
    if(r<55) return "Pests";
    return "Normal";
}
string Weather::triggerEvent(int randomVal)
{
    if(randomVal<20) return "🌧️ Rain";      // 20%
    if(randomVal<40) return "🌞 Sunny";     // 20%
    if(randomVal<50) return "🐛 Pests";     // 10%
    return "🌫️ Normal";                     // 50%
}

string Weather::getForecast()
{
    int r=rand()%3;
    if(r==0) return "🌞 Sunny";
    if(r==1) return "🌧️ Rain";
    return "🌫️ Normal";
}
