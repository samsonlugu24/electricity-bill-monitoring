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
