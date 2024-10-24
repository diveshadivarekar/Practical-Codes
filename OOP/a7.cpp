#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    map<string, long long> statePopulation;

    statePopulation["Maharashtra"] = 39;
    statePopulation["UttarPradesh"] = 29;
    statePopulation["Delhi"] = 21;
    statePopulation["Punjab"] = 20;
    statePopulation["Bengal"] = 13;

    string stateName;

    cout << "Enter the name of a state: ";
    getline(cin, stateName);

    auto it = statePopulation.find(stateName);

    if (it != statePopulation.end()) {
        cout << "The population of " << stateName << " is " << it->second << endl;
    } else {
        cout << "State not found in the database!" << endl;
    }

    return 0;
}
