#include "Plant.h"
#include "Colors.h"
#include <iostream>
using namespace std;
#pragma once
Plant::Plant()
{
    name = "Seed";
    water = 5;
    sun = 5;
    fertilizer = 0;
    growth = 0;
    health = 10;
    isAlive = true;
    hasPests = false;
}

void Plant::setName(string n) { name = n; }
string Plant::getName() { return name; }

void Plant::addWater()
{
    if (!isAlive) return;
    water += 3;
    if (water > 10) water = 10;
}

void Plant::addSun()
{
    if (!isAlive) return;
    sun += 3;
    if (sun > 10) sun = 10;
}

void Plant::addFertilizer()
{
    if (!isAlive) return;
    fertilizer += 5;
    if (fertilizer > 10) fertilizer = 10;
    hasPests = false;
}

void Plant::infest()
{
    hasPests = true;
}

void Plant::processDay()
{
    if (!isAlive) return;

    water -= 1;
    sun -= 1;

    if (hasPests)
        health -= 2;

    if (water <= 0 || sun <= 0)
        health -= 1;

    if (health <= 0)
    {
        isAlive = false;
        health = 0;
    }
}

void Plant::grow()
{
    if (!isAlive) return;

    if (water > 3 && sun > 3 && health > 5)
    {
        int boost = 1;
        if (fertilizer > 0)
        {
            boost = 2;
            fertilizer--;
        }
        growth += boost;
    }

    if (growth > 30) growth = 30;
}

// Getters
int Plant::getWater() { return water; }
int Plant::getSun() { return sun; }
int Plant::getHealth() { return health; }
int Plant::getGrowth() { return growth; }
bool Plant::checkAlive() { return isAlive; }
bool Plant::checkPests() { return hasPests; }

// Plant value
int Plant::getSellValue()
{
    if (!isAlive) return 0;
    int value = growth * 2;
    if (growth >= 30) value += 50;
    return value;
}

// ✅ Fixed printStatus with colors and emojis
void Plant::printStatus()
{
    bool alive = checkAlive();
    bool pests = checkPests();

    string statusColor = alive ? GREEN : RED;
    string aliveEmoji = alive ? "🌱" : "💀";
    string pestEmoji = pests ? "🐛" : "";

    cout << aliveEmoji << " " << BOLD << name << RESET
         << " | HP: " << statusColor << health << "/10" << RESET
         << " | G: " << growth << "/30"
         << " | 💧 " << water
         << " | 🌞 " << sun
         << " | 🌿 " << fertilizer
         << " " << pestEmoji
         << " | $" << YELLOW << getSellValue() << RESET
         << endl;
}

// File I/O
void Plant::save(ofstream &file)
{
    file << name << " " << water << " " << sun << " " << fertilizer 
         << " " << growth << " " << health << " " << isAlive << " " << hasPests << endl;
}

void Plant::load(ifstream &file)
{
    file >> name >> water >> sun >> fertilizer
         >> growth >> health >> isAlive >> hasPests;
}
