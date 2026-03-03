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

// -------- File Saving --------
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

// -------- File Loading --------
void loadFile(Appliance list[], int &count) {
    count = 0;
    ifstream file(APPLIANCE_FILE);

    if (!file)
        return;

    string line;

    while (getline(file, line)) {
        int p1 = line.find("|");
        int p2 = line.find("|", p1 + 1);

        if (p1 == -1 || p2 == -1)
            continue;

        list[count].name = line.substr(0, p1);
        list[count].watts = atof(line.substr(p1 + 1, p2 - p1 - 1).c_str());
        list[count].hours = atof(line.substr(p2 + 1).c_str());

        count++;
        if (count >= MAX)
            break;
    }

    file.close();
}

// -------- Add Appliance --------
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
    saveFile(list, count);

    cout << "Appliance added and saved.\n";
}

// -------- View Appliances --------
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

// -------- Search Appliance --------
void searchAppliance(Appliance list[], int count) {
    if (count == 0) {
        cout << "No appliances available.\n";
        return;
    }

    cin.ignore();

    string search;
    cout << "Enter name to search: ";
    getline(cin, search);

    bool found = false;

    for (int i = 0; i < count; i++) {
        if (list[i].name.find(search) != string::npos) {
            cout << list[i].name << " | "
                 << calculateKwh(list[i].watts, list[i].hours)
                 << " kWh/day\n";
            found = true;
        }
    }

    if (!found)
        cout << "Appliance not found.\n";
}

// -------- Billing --------
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
    double costDay = totalDay * tariff;
    double costMonth = totalMonth * tariff;

    cout << fixed << setprecision(2);
    cout << "\nDaily Energy: " << totalDay << " kWh\n";
    cout << "Monthly Energy: " << totalMonth << " kWh\n";
    cout << "Daily Cost: " << costDay << "\n";
    cout << "Monthly Cost: " << costMonth << "\n";

    cout << "\nSave billing summary? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        ofstream file(BILLING_FILE, ios::app);

        file << "------ BILLING SUMMARY ------\n";
        file << "Tariff: " << tariff << "\n";
        file << "Daily kWh: " << totalDay << "\n";
        file << "Monthly kWh: " << totalMonth << "\n";
        file << "Daily Cost: " << costDay << "\n";
        file << "Monthly Cost: " << costMonth << "\n";
        file << "-----------------------------\n\n";

        file.close();

        cout << "Billing summary saved.\n";
    }
}

// -------- Main --------
int main() {
    Appliance list[MAX];
    int count = 0;
    int option;

    loadFile(list, count);

    do {
        cout << "\n==== Electrical Load Monitoring ====\n";
        cout << "1. Add Appliance\n";
        cout << "2. View Appliances\n";
        cout << "3. Search Appliance\n";
        cout << "4. Billing\n";
        cout << "5. Exit\n";
        cout << "Choose: ";
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
            cout << "Goodbye.\n";
        }
        else
            cout << "Invalid option.\n";

    } while (option != 5);

    return 0;
}