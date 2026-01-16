#ifndef PAYMENT_H
#define PAYMENT_H

class Payment
{
private:
    int wallet;
    int bank;

public:
    Payment();

    int getWalletBalance();
    int getBankBalance();

    bool payCash(int amount);  // pay from wallet
    void addCash(int amount);  // add to wallet

    bool withdraw(int amount); // bank -> wallet
    bool deposit(int amount);  // wallet -> bank

    void save(std::ofstream &file);
    void load(std::ifstream &file);
};

#endif
