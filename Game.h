#ifndef GAME_H
#define GAME_H

#include "Plant.cpp"
#include "Payment.cpp"
#include "Gardener.cpp"
#include "Weather.cpp"

const int MAX_GARDEN_SIZE = 5;

class Game
{
private:
    Plant plants[MAX_GARDEN_SIZE];
    int plantCount;

    Weather weather;
    Gardener gardener;
    Payment finances;

    int day;

    int getIntInput(int min, int max);

public:
    Game();

    void start();
    void menu();

    void nextDay();
    void addPlant();
    void sellPlant();

    void manageGardener();
    void processPayment();
    void visitBank();

    void saveGame();
    void loadGame();
};

#endif
