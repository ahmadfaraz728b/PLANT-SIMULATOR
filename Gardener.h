#ifndef GARDENER_H
#define GARDENER_H

#include "Plant.cpp"

class Gardener
{
private:
    bool hired;
    int salary;

public:
    Gardener();
    bool checkHired();
    void hire(int s);
    void fire();
    void work(Plant *plants, int count);

    void save(std::ofstream &file);
    void load(std::ifstream &file);
};

#endif
