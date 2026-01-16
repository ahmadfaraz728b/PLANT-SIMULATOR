#include "Game.h"
#include "Colors.cpp"
#include <iostream>
#include <fstream>
using namespace std;

Game::Game()
{
    plantCount = 0;
    day = 1;
}

// Input with validation
int Game::getIntInput(int min, int max)
{
    int val;
    while (true)
    {
        cin >> val;
        if (cin.fail() || val < min || val > max)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << RED << "Invalid input. Try again: " << RESET;
        }
        else
            return val;
    }
}

// Start game
void Game::start()
{
    cout << BOLD << GREEN << "\n=== 🌳 YOUR GARDEN SIMULATOR 🌳 ===" << RESET << endl;
    loadGame();
    menu();
}

// Main menu
void Game::menu()
{
    while (true)
    {
        cout << BOLD << "\nDay " << day 
             << " | 💵 Wallet: $" << finances.getWalletBalance()
             << " | 🏦 Bank: $" << finances.getBankBalance() << RESET << endl;
        
        string forecast = weather.getForecast();
        cout << CYAN << "Forecast: " << forecast << RESET << endl;

        if (plantCount == 0)
            cout << YELLOW << "🌿 Your garden is empty." << RESET << endl;

        for (int i = 0; i < plantCount; i++)
        {
            cout << BOLD << i + 1 << ". " << RESET;
            plants[i].printStatus();
        }

        cout << "\n1. 🌱 Plant a Seed ($10)"
             << "\n2. 💧 Water a Plant"
             << "\n3. 🌞 Give Sun to a Plant"
             << "\n4. 🌿 Fertilize a Plant"
             << "\n5. 💰 Sell a Plant"
             << "\n6. 👨‍🌾 Manage Gardener"
             << "\n7. 🏦 Bank Services"
             << "\n8. 💤 Next Day"
             << "\n9. 💾 Save & Exit"
             << "\nSelect: ";

        int choice = getIntInput(1, 9);

        switch (choice)
        {
            case 1: addPlant(); break;
            case 2:
                if (plantCount == 0) cout << RED << "No plants!" << RESET << endl;
                else
                {
                    cout << "Plant # (1-" << plantCount << "): ";
                    int idx = getIntInput(1, plantCount);
                    plants[idx - 1].addWater();
                    cout << CYAN << "Watered." << RESET << endl;
                }
                break;
            case 3:
                if (plantCount == 0) cout << RED << "No plants!" << RESET << endl;
                else
                {
                    cout << "Plant # (1-" << plantCount << "): ";
                    int idx = getIntInput(1, plantCount);
                    plants[idx - 1].addSun();
                    cout << YELLOW << "Given Sun." << RESET << endl;
                }
                break;
            case 4:
                if (plantCount == 0) cout << RED << "No plants!" << RESET << endl;
                else
                {
                    cout << "Plant # (1-" << plantCount << "): ";
                    int idx = getIntInput(1, plantCount);
                    plants[idx - 1].addFertilizer();
                    cout << GREEN << "Fertilized." << RESET << endl;
                }
                break;
            case 5: sellPlant(); break;
            case 6: manageGardener(); break;
            case 7: visitBank(); break;
            case 8: nextDay(); break;
            case 9: saveGame(); return;
        }
    }
}

// Add new plant
void Game::addPlant()
{
    if (plantCount >= MAX_GARDEN_SIZE)
    {
        cout << RED << "Garden is full!" << RESET << endl;
        return;
    }

    if (!finances.payCash(10))
    {
        cout << RED << "Not enough cash!" << RESET << endl;
        return;
    }

    cout << "Enter Plant Name: ";
    string n;
    cin >> n;
    plants[plantCount].setName(n);
    plantCount++;

    cout << GREEN << "New seed planted!" << RESET << endl;
}

// Sell plant
void Game::sellPlant()
{
    if (plantCount == 0)
    {
        cout << RED << "No plants to sell!" << RESET << endl;
        return;
    }

    cout << "Select plant # (1-" << plantCount << "): ";
    int idx = getIntInput(1, plantCount) - 1;

    int value = plants[idx].getSellValue();
    string name = plants[idx].getName();

    if (value == 0) cout << RED << "Dead plant! Worth nothing." << RESET << endl;
    else
    {
        cout << YELLOW << "Selling " << name << " for $" << value << "..." << RESET << endl;
        finances.addCash(value);
    }

    for (int i = idx; i < plantCount - 1; i++) plants[i] = plants[i + 1];
    plantCount--;
}

// Next Day
void Game::nextDay()
{
    day++;
    cout << "\n" << BLUE << "--- Day " << day << " ---" << RESET << endl;

    for (int i = 0; i < plantCount; i++)
    {
        plants[i].processDay();
        plants[i].grow();
    }

    if (gardener.checkHired()) processPayment();

    cout << GREEN << "Day ended. Plants updated." << RESET << endl;
}

// Bank Services
void Game::visitBank()
{
    cout << "\n" << CYAN << "--- Bank Services ---" << RESET << endl;
    cout << "1. Withdraw\n2. Deposit\n3. Cancel\nSelect: ";
    int c = getIntInput(1, 3);
    if (c == 1)
    {
        cout << "Amount to withdraw: ";
        int amt; cin >> amt;
        if (finances.withdraw(amt)) cout << GREEN << "Withdrawn successfully!" << RESET << endl;
        else cout << RED << "Insufficient funds!" << RESET << endl;
    }
    else if (c == 2)
    {
        cout << "Amount to deposit: ";
        int amt; cin >> amt;
        if (finances.deposit(amt)) cout << GREEN << "Deposited successfully!" << RESET << endl;
        else cout << RED << "Not enough cash!" << RESET << endl;
    }
}

// Manage gardener (simplified)
void Game::manageGardener()
{
    cout << YELLOW << "Gardener management coming soon..." << RESET << endl;
}

// Payment to gardener
void Game::processPayment()
{
    // Placeholder: implement salary logic here
}

// Save game
void Game::saveGame()
{
    ofstream file("savegame.txt");
    if (!file) { cout << RED << "Error saving game!" << RESET << endl; return; }

    file << day << " " << plantCount << endl;
    finances.save(file);
    for (int i = 0; i < plantCount; i++) plants[i].save(file);
    gardener.save(file);
    file.close();
    cout << GREEN << "Game saved!" << RESET << endl;
}

// Load game
void Game::loadGame()
{
    ifstream file("savegame.txt");
    if (!file) return;

    file >> day >> plantCount;
    finances.load(file);
    for (int i = 0; i < plantCount; i++) plants[i].load(file);
    gardener.load(file);
    file.close();
    cout << GREEN << "Previous game loaded!" << RESET << endl;
}
