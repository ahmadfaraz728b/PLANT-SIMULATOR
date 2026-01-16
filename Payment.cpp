#include "Payment.h"
#include <fstream>
Payment::Payment() { wallet = 100; bank = 0; }

int Payment::getWalletBalance() { return wallet; }
int Payment::getBankBalance() { return bank; }

bool Payment::payCash(int amount)
{
    if(wallet >= amount) { wallet -= amount; return true; }
    return false;
}

void Payment::addCash(int amount) { wallet += amount; }

bool Payment::withdraw(int amount)
{
    if(bank >= amount) { bank -= amount; wallet += amount; return true; }
    return false;
}

bool Payment::deposit(int amount)
{
    if(wallet >= amount) { wallet -= amount; bank += amount; return true; }
    return false;
}

void Payment::save(std::ofstream &file)
{
    file << wallet << " " << bank << std::endl;
}

void Payment::load(std::ifstream &file)
{
    file >> wallet >> bank;
}
