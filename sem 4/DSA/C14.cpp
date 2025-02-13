#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <climits>

using namespace std;

class cityGraph {
    unordered_map<string, unordered_map<string, int>> city;
    unordered_set<string> citylist;

public:
    void add_city(string cityA, string cityB) {
        citylist.insert(cityA);
        citylist.insert(cityB);
    }


    void add_cost(string cityA, string cityB, int cost) {
        city[cityA][cityB] = cost;
        city[cityB][cityA] = cost;
    }

    void list_city() {
        for (string city : citylist) {
            cout << city << endl;
        }
    }

    void list_city_cost() {
        for (auto pair : city) {
            cout << pair.first << " connects to: ";
            for (auto conn : pair.second) {
                cout << conn.first << " with cost " << conn.second << ", ";
            }
            cout << endl;
        }
    }

    void print_matrix() {
        vector<string> cityVector(citylist.begin(), citylist.end());

        unordered_map<string, int> cityIndex;
        for (int i = 0; i < cityVector.size(); i++) {
            cityIndex[cityVector[i]] = i;
        }

        cout << "     ";
        for (string city : cityVector) {
            cout << city << "   ";
        }
        cout << endl;

        for (string cityA : cityVector) {
            cout << cityA << "   ";
            for (string cityB : cityVector) {

                if (city[cityA].count(cityB)) {
                    cout << city[cityA][cityB] << "   "; 
                } else {
                    cout << "0   ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    cityGraph cg;

    cg.add_cost("A", "B", 10);
    cg.add_cost("B", "C", 20);
    cg.add_cost("C", "D", 30);
    cg.add_cost("D", "E", 40);

    cg.add_city("A", "B");
    cg.add_city("B", "C");
    cg.add_city("C", "D");
    cg.add_city("D", "E");

    cg.print_matrix();
    // cg.list_city_cost();
    // cg.list_city();

    return 0;
}