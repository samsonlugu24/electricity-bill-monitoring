#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX = 100;

struct Appliance {
    string name;
    double watts;
    double hours;
};

void addAppliance(Appliance list[], int &count) {
    if (count >= MAX) {
        cout << "Maximum limit reached.\n";
        return;
    }

    cin.ignore();

    cout << "Enter appliance name: ";
    getline(cin, list[count].name);

    cout << "Enter watts: ";
    cin >> list[count].watts;

    cout << "Enter hours per day: ";
    cin >> list[count].hours;

    count++;
    cout << "Appliance added.\n";
}

void viewAppliances(Appliance list[], int count) {
    if (count == 0) {
        cout << "No appliances available.\n";
        return;
    }

    cout << left << setw(5) << "No"
         << setw(20) << "Name"
         << setw(10) << "Watts"
         << setw(10) << "Hours\n";

    for (int i = 0; i < count; i++) {
        cout << left << setw(5) << i + 1
             << setw(20) << list[i].name
             << setw(10) << list[i].watts
             << setw(10) << list[i].hours
             << "\n";
    }
}

int main() {
    Appliance list[MAX];
    int count = 0;
    int option;

    do {
        cout << "\n=== Appliance Manager ===\n";
        cout << "1. Add Appliance\n";
        cout << "2. View Appliances\n";
        cout << "3. Exit\n";
        cout << "Choose: ";
        cin >> option;

        if (option == 1)
            addAppliance(list, count);
        else if (option == 2)
            viewAppliances(list, count);
        else if (option == 3)
            cout << "Goodbye.\n";
        else
            cout << "Invalid option.\n";

    } while (option != 3);

    return 0;
}