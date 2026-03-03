#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX = 100;
const string APPLIANCE_FILE = "appliances.txt";
const string BILLING_FILE = "billing_summary.txt";

struct Appliance {
    string name;
    double watts;
    double hours;
};

double calculateKwh(double watts, double hours) {
    return (watts / 1000) * hours;
}

void saveFile(Appliance list[], int count) {
    ofstream file(APPLIANCE_FILE);

    if (!file) {
        cout << "Error saving file.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        file << list[i].name << "|"
             << list[i].watts << "|"
             << list[i].hours << "\n";
    }

    file.close();
}

void loadFile(Appliance list[], int &count) {
    count = 0;

    ifstream file(APPLIANCE_FILE);

    if (!file)
        return;

    string line;

    while (getline(file, line)) {
        int pos1 = line.find("|");
        int pos2 = line.find("|", pos1 + 1);

        if (pos1 == -1 || pos2 == -1)
            continue;

        list[count].name = line.substr(0, pos1);
        list[count].watts = atof(line.substr(pos1 + 1, pos2 - pos1 - 1).c_str());
        list[count].hours = atof(line.substr(pos2 + 1).c_str());

        count++;
        if (count >= MAX)
            break;
    }

    file.close();
}

void addAppliance(Appliance list[], int &count) {
    if (count >= MAX) {
        cout << "Maximum limit reached.\n";
        return;
    }

    cin.ignore();

    cout << "Enter name: ";
    getline(cin, list[count].name);

    cout << "Enter watts: ";
    cin >> list[count].watts;

    cout << "Enter hours per day: ";
    cin >> list[count].hours;

    count++;

    saveFile(list, count);

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

void searchAppliance(Appliance list[], int count) {
    if (count == 0) {
        cout << "No appliances available.\n";
        return;
    }

    cin.ignore();

    string name;
    cout << "Enter name to search: ";
    getline(cin, name);

    bool found = false;

    for (int i = 0; i < count; i++) {
        if (list[i].name.find(name) != string::npos) {
            cout << list[i].name << " - "
                 << calculateKwh(list[i].watts, list[i].hours)
                 << " kWh/day\n";
            found = true;
        }
    }

    if (!found)
        cout << "Appliance not found.\n";
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

    cout << "Save billing summary? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        ofstream file(BILLING_FILE, ios::app);

        file << "Tariff: " << tariff << "\n";
        file << "Daily kWh: " << totalDay << "\n";
        file << "Monthly kWh: " << totalMonth << "\n";
        file << "Daily Cost: " << totalDay * tariff << "\n";
        file << "Monthly Cost: " << totalMonth * tariff << "\n";
        file << "-------------------------\n";

        file.close();

        cout << "Summary saved.\n";
    }
}

int main() {
    Appliance list[MAX];
    int count = 0;

    loadFile(list, count);

    int option;

    do {
        cout << "\n==== Electrical Load Monitoring ====\n";
        cout << "1. Add Appliance\n";
        cout << "2. View Appliances\n";
        cout << "3. Search Appliance\n";
        cout << "4. Billing\n";
        cout << "5. Save\n";
        cout << "6. Exit\n";
        cout << "Select option: ";

        cin >> option;

        if (option == 1)
            addAppliance(list, count);
        else if (option == 2)
            viewAppliances(list, count);
        else if (option == 3)
            searchAppliance(list, count);
        else if (option == 4)
            billing(list, count);
        else if (option == 5) {
            saveFile(list, count);
            cout << "Saved.\n";
        }
        else if (option == 6) {
            saveFile(list, count);
            cout << "Exiting program.\n";
        }
        else
            cout << "Invalid option.\n";

    } while (option != 6);

    return 0;
}
