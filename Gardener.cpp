#include "Gardener.h"
#include <iostream>

Gardener::Gardener()
{
    hired = false;
    salary = 0;
}

bool Gardener::checkHired() { return hired; }

void Gardener::hire(int s)
{
    hired = true;
    salary = s;
}

void Gardener::fire()
{
    hired = false;
    salary = 0;
}

void Gardener::work(Plant* plants, int count)
{
    if (!hired) return;

    for (int i = 0; i < count; i++)
    {
        if (plants[i].checkAlive())
        {
            plants[i].addWater();
            plants[i].addSun();
            plants[i].addFertilizer();
        }
    }

    std::cout << "Gardener worked on your garden today.\n";
}

void Gardener::save(std::ofstream &file)
{
    file << hired << " " << salary << "\n";
}

void Gardener::load(std::ifstream &file)
{
    file >> hired >> salary;
}
