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

double calculateKwh(double watts, double hours) {
    return (watts / 1000) * hours;
}

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

    cout << fixed << setprecision(2);

    cout << left << setw(5) << "No"
         << setw(20) << "Name"
         << setw(10) << "Watts"
         << setw(10) << "Hours"
         << setw(10) << "kWh\n";

    for (int i = 0; i < count; i++) {
        cout << left << setw(5) << i + 1
             << setw(20) << list[i].name
             << setw(10) << list[i].watts
             << setw(10) << list[i].hours
             << setw(10) << calculateKwh(list[i].watts, list[i].hours)
             << "\n";
    }
}

void billing(Appliance list[], int count) {
    if (count == 0) {
        cout << "No appliances available.\n";
        return;
    }

    double tariff;
    cout << "Enter tariff per kWh: ";
    cin >> tariff;

    double totalDay = 0;

    for (int i = 0; i < count; i++) {
        totalDay += calculateKwh(list[i].watts, list[i].hours);
    }

    double totalMonth = totalDay * 30;

    cout << fixed << setprecision(2);
    cout << "Daily Energy: " << totalDay << " kWh\n";
    cout << "Monthly Energy: " << totalMonth << " kWh\n";
    cout << "Daily Cost: " << totalDay * tariff << "\n";
    cout << "Monthly Cost: " << totalMonth * tariff << "\n";
}

int main() {
    Appliance list[MAX];
    int count = 0;
    int option;

    do {
        cout << "\n=== Electrical Load Monitoring ===\n";
        cout << "1. Add Appliance\n";
        cout << "2. View Appliances\n";
        cout << "3. Billing\n";
        cout << "4. Exit\n";
        cout << "Choose: ";
        cin >> option;

        if (option == 1)
            addAppliance(list, count);
        else if (option == 2)
            viewAppliances(list, count);
        else if (option == 3)
            billing(list, count);
        else if (option == 4)
            cout << "Goodbye.\n";
        else
            cout << "Invalid option.\n";

    } while (option != 4);

    return 0;
}