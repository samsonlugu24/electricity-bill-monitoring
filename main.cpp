#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX = 100;
const string FILE_NAME = "appliances.txt";

struct Appliance {
    string name;
    double watts;
    double hours;
};

double calculateKwh(double watts, double hours) {
    return (watts / 1000) * hours;
}

void saveFile(Appliance list[], int count) {
    ofstream file(FILE_NAME);
    for (int i = 0; i < count; i++) {
        file << list[i].name << "|"
             << list[i].watts << "|"
             << list[i].hours << "\n";
    }
    file.close();
}

void loadFile(Appliance list[], int &count) {
    count = 0;
    ifstream file(FILE_NAME);
    if (!file) return;

    string line;
    while (getline(file, line)) {
        int p1 = line.find("|");
        int p2 = line.find("|", p1 + 1);
        if (p1 == -1 || p2 == -1) continue;

        list[count].name = line.substr(0, p1);
        list[count].watts = atof(line.substr(p1 + 1, p2 - p1 - 1).c_str());
        list[count].hours = atof(line.substr(p2 + 1).c_str());

        count++;
        if (count >= MAX) break;
    }
    file.close();
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

void deleteAppliance(Appliance list[], int &count) {
    if (count == 0) {
        cout << "No appliances to delete.\n";
        return;
    }

    viewAppliances(list, count);

    int num;
    cout << "Enter appliance number to delete: ";
    cin >> num;

    if (num < 1 || num > count) {
        cout << "Invalid number.\n";
        return;
    }

    for (int i = num - 1; i < count - 1; i++) {
        list[i] = list[i + 1];
    }

    count--;
    saveFile(list, count);

    cout << "Appliance deleted.\n";
}

void editAppliance(Appliance list[], int count) {
    if (count == 0) {
        cout << "No appliances to edit.\n";
        return;
    }

    viewAppliances(list, count);

    int num;
    cout << "Enter appliance number to edit: ";
    cin >> num;

    if (num < 1 || num > count) {
        cout << "Invalid number.\n";
        return;
    }

    cin.ignore();
    cout << "New name: ";
    getline(cin, list[num - 1].name);

    cout << "New watts: ";
    cin >> list[num - 1].watts;

    cout << "New hours per day: ";
    cin >> list[num - 1].hours;

    saveFile(list, count);

    cout << "Appliance updated.\n";
}

int main() {
    Appliance list[MAX];
    int count = 0;
    int option;

    loadFile(list, count);

    do {
        cout << "\n==== Electrical Load Monitoring ====\n";
        cout << "1. Add Appliance\n";
        cout << "2. View Appliances\n";
        cout << "3. Delete Appliance\n";
        cout << "4. Edit Appliance\n";
        cout << "5. Exit\n";
        cout << "Choose: ";
        cin >> option;

        if (option == 1)
            addAppliance(list, count);
        else if (option == 2)
            viewAppliances(list, count);
        else if (option == 3)
            deleteAppliance(list, count);
        else if (option == 4)
            editAppliance(list, count);
        else if (option == 5)
            cout << "Goodbye.\n";
        else
            cout << "Invalid option.\n";

    } while (option != 5);

    return 0;
}
