#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Item {
    int code;
    string name;
    float cost;
    int quantity;

    friend ostream& operator<<(ostream& os, const Item& item) {
        os << "Code: " << item.code << ", Name: " << item.name 
           << ", Cost: " << item.cost << ", Quantity: " << item.quantity;
        return os;
    }
};

bool compareByCode(const Item& a, const Item& b) {
    return a.code < b.code;
}

void displayItems(const vector<Item>& items) {
    for (const auto& item : items) {
        cout << item << endl;
    }
}

void searchItem(const vector<Item>& items, int code) {
    auto it = find_if(items.begin(), items.end(), [code](const Item& item) {
        return item.code == code;
    });

    if (it != items.end()) {
        cout << "Item found: " << *it << endl;
    } else {
        cout << "Item with code " << code << " not found!" << endl;
    }
}

int main() {
    vector<Item> items;
    int n;

    cout << "Enter number of items: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        Item item;
        cout << "Enter details for item " << i + 1 << ":\n";
        cout << "Code: ";
        cin >> item.code;
        cout << "Name: ";
        cin.ignore(); // To consume the newline character
        getline(cin, item.name);
        cout << "Cost: ";
        cin >> item.cost;
        cout << "Quantity: ";
        cin >> item.quantity;
        items.push_back(item);
    }

    sort(items.begin(), items.end(), compareByCode);

    cout << "\nItems sorted by code:\n";
    displayItems(items);

    int searchCode;
    cout << "\nEnter item code to search: ";
    cin >> searchCode;
    searchItem(items, searchCode);

    return 0;
}
