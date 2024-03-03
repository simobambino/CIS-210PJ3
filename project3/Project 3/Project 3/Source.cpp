#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class ItemTracker {
private:
    map<string, int> itemFrequencies;

public:
    void loadData(string filename);
    int searchItem(string item);
    void printFrequencies();
    void printHistogram();
    void backupData(string filename);
};

void ItemTracker::loadData(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string item;
    while (file >> item) {
        itemFrequencies[item]++;
    }

    file.close();
}

int ItemTracker::searchItem(string item) {
    return itemFrequencies[item];
}

void ItemTracker::printFrequencies() {
    cout << "Item Frequencies:" << endl;
    for (const auto& pair : itemFrequencies) {
        cout << pair.first << " " << pair.second << endl;
    }
}

void ItemTracker::printHistogram() {
    cout << "Item Histogram:" << endl;
    for (const auto& pair : itemFrequencies) {
        cout << pair.first << " ";
        for (int i = 0; i < pair.second; ++i) {
            cout << "*";
        }
        cout << endl;
    }
}

void ItemTracker::backupData(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to create backup file " << filename << endl;
        return;
    }

    for (const auto& pair : itemFrequencies) {
        file << pair.first << " " << pair.second << endl;
    }

    file.close();
}


int main() {
    ItemTracker tracker;
    string filename = "CS210_Project_Three_Input_File.txt";
    tracker.loadData(filename);

    int choice;
    do {
        cout << "Menu Options:" << endl;
        cout << "1. Search for item" << endl;
        cout << "2. Print item frequencies" << endl;
        cout << "3. Print histogram" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string item;
            cout << "Enter the item to search: ";
            cin >> item;
            int frequency = tracker.searchItem(item);
            cout << "Frequency of " << item << ": " << frequency << endl;
            break;
        }
        case 2:
            tracker.printFrequencies();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            tracker.backupData("frequency.dat");
            cout << "Data backup created successfully." << endl;
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    } while (choice != 4);

    return 0;
}
