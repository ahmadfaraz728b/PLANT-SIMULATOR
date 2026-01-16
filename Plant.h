#ifndef PLANT_H
#define PLANT_H
#pragma once
#include <string>
#include <fstream>
using namespace std;

class Plant
{
private:
    string name;
    int water;
    int sun;
    int fertilizer;
    int growth;
    int health;
    bool isAlive;
    bool hasPests;

public:
    Plant();

    void setName(string n);
    string getName();

    // Actions
    void addWater();
    void addSun();
    void addFertilizer();
    void infest();

    // Daily logic
    void processDay();
    void grow();

    // Getters
    int getWater();
    int getSun();
    int getHealth();
    int getGrowth();
    bool checkAlive();
    bool checkPests();

    // Calculate plant sell value
    int getSellValue();

    // Display
    void printStatus();

    // File I/O
    void save(ofstream &file);
    void load(ifstream &file);
};

#endif
