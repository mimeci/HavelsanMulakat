#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> name;
vector<int> amount;
vector<float> price;
vector<int> coins;
static int availableMoney = 0;


void parseDrinkData(string& data) {
    const string comma = ",";
    const string dollar = "$";
    
    // storing drink name
    size_t found1 = data.find(comma);
    if (found1 != string::npos)
        ::name.push_back(data.substr(0, found1));

    // storing drink amount
    size_t found2 = data.find(comma, found1 + 1);
    if (found2 != string::npos)
        ::amount.push_back(stoi(data.substr(found1 + 1, found2)));

    // storing drink price
    size_t found3 = data.find(dollar, found2 + 1);
    if (found3 != string::npos)
        ::price.push_back(stof(data.substr(found2 + 1, found3)));

}

void parseAvailableCoins(string& coinTypes)
{
    const string comma = ",";
    size_t prevFound = 0;

    // storing available coin types
    for (int i = 0; i < coinTypes.size();)
    {
        size_t found1 = coinTypes.find(comma, prevFound + 1);
        if (found1 > coinTypes.size())
            found1 = coinTypes.size();

        if (found1 != string::npos)
            if (coinTypes.at(found1 - 1) == 'c')
                if (prevFound == 0)
                    ::coins.push_back(stoi(coinTypes.substr(prevFound, found1 - 1)));
                else
                    ::coins.push_back(stoi(coinTypes.substr(prevFound + 1, found1 - 1)));
            else if (coinTypes.at(found1 - 1) == '$')
                if (prevFound == 0)
                    ::coins.push_back(stoi(coinTypes.substr(prevFound, found1 - 1)) * 100);
                else
                    ::coins.push_back(stoi(coinTypes.substr(prevFound + 1, found1 - 1)) * 100);

        i = found1;
        prevFound = found1;
    }
}

void updateAvailableMoney(string& s) {
    if (s.substr(s.size() - 1, s.size()) == "c")
        availableMoney = availableMoney + stoi(s.substr(0, s.size() - 1));
    else if (s.substr(s.size() - 1, s.size()) == "$")
        availableMoney = availableMoney + (stoi(s.substr(0, s.size() - 1)) * 100);

}

void displayMainWindow()
{
    cout << "Drink - Amount - Price" <<"\n";
    fstream newfile;
    newfile.open("Prices.txt", ios::in);
    if (newfile.is_open()) {
        string tp;
        int counter = 0;
        while (getline(newfile, tp)) {
            parseDrinkData(tp);

            if (::amount.at(counter) != 0)
                cout << tp << "\n";
            counter++;
        }
        newfile.close();
    }

    newfile.open("Coins.txt", ios::in);
    if (newfile.is_open()) {
        string coinTypes;
        getline(newfile, coinTypes);
        parseAvailableCoins(coinTypes);

        cout << "\nAvailable coin types:\n" << coinTypes << "\n\n";
    }
    newfile.close();
}

void takeMoney() {
    string money;
    string answer;

    while (1) {
        cout << "Please insert a coin:\n";
        cin >> money;
        updateAvailableMoney(money);
        
        cout << "Available Money: " << availableMoney << " cent\n";
        cout << "Would you like to insert more coins? Y/N" << "\n";
        cin >> answer;
        if (answer == "N")
            break;
    }
}


int main()
{
    displayMainWindow();
    takeMoney();
    return 0;
}