/*
 * ============================================================
 *  Rwanda Ministry of Infrastructure - Road Management System
 *  DSA National Exam Solution  (v2 - robust input handling)
 * ============================================================
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
using namespace std;

// ─── Constants & Global Data ────────────────────────────────
const int MAX = 100;

string cities[MAX];          // City names  (0-based internally)
int    roads[MAX][MAX];      // Adjacency matrix: 1 = road, 0 = no road
double budgets[MAX][MAX];    // Adjacency matrix: budget in Billion RWF
int    numCities = 0;

// ════════════════════════════════════════════════════════════
//  UTILITY FUNCTIONS
// ════════════════════════════════════════════════════════════

// Remove leading/trailing spaces AND the Windows '\r' character
string trim(string s) {
    // remove trailing \r, \n, spaces
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n' || s.back() == ' '))
        s.pop_back();
    // remove leading spaces
    size_t start = s.find_first_not_of(' ');
    return (start == string::npos) ? "" : s.substr(start);
}

// Read a clean line (handles Windows \r\n and stray newlines)
string readLine(const string& prompt) {
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        line = trim(line);
        if (!line.empty()) return line;
        cout << "  [!] Input cannot be empty. Please try again.\n";
    }
}

// Read a positive integer with validation
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Invalid input. Please enter a positive integer.\n";
    }
}

// Read a positive double with validation
double readDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Invalid input. Please enter a positive number.\n";
    }
}

void initArrays() {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++) {
            roads[i][j]   = 0;
            budgets[i][j] = 0.0;
        }
}

// Returns 0-based index of city, or -1 if not found
int findByName(const string& name) {
    for (int i = 0; i < numCities; i++)
        if (cities[i] == name) return i;
    return -1;
}

// ════════════════════════════════════════════════════════════
//  MENU 1 — Add New City(ies)
// ════════════════════════════════════════════════════════════
void addCities() {
    int n = readInt("Enter the number of cities to add: ");

    int added = 0;
    while (added < n) {
        string name = readLine("Enter the name for city " + to_string(numCities + 1) + ": ");

        if (findByName(name) != -1) {
            cout << "  [!] City '" << name << "' already exists. Enter a different name.\n";
            // Do NOT advance added — ask again for this slot
            continue;
        }

        cities[numCities++] = name;
        cout << "  [+] '" << name << "' recorded as city #" << numCities << ".\n";
        added++;
    }
    cout << "Done. " << n << " city(ies) added.\n";
}

// ════════════════════════════════════════════════════════════
//  MENU 2 — Add Road Between Two Cities
// ════════════════════════════════════════════════════════════
void addRoad() {
    string c1 = readLine("Enter the name of the first city : ");
    string c2 = readLine("Enter the name of the second city: ");

    int i = findByName(c1);
    int j = findByName(c2);

    if (i == -1) { cout << "  [!] City '" << c1 << "' not found.\n"; return; }
    if (j == -1) { cout << "  [!] City '" << c2 << "' not found.\n"; return; }
    if (i == j)  { cout << "  [!] A city cannot have a road to itself.\n"; return; }
    if (roads[i][j]) {
        cout << "  [!] A road already exists between " << c1 << " and " << c2 << ".\n";
        return;
    }

    roads[i][j] = roads[j][i] = 1;
    cout << "Road added successfully between " << c1 << " and " << c2 << ".\n";
}

// ════════════════════════════════════════════════════════════
//  MENU 3 — Add Budget for a Road
// ════════════════════════════════════════════════════════════
void addBudget() {
    string c1 = readLine("Enter the name of the first city : ");
    string c2 = readLine("Enter the name of the second city: ");

    int i = findByName(c1);
    int j = findByName(c2);

    if (i == -1) { cout << "  [!] City '" << c1 << "' not found.\n"; return; }
    if (j == -1) { cout << "  [!] City '" << c2 << "' not found.\n"; return; }
    if (!roads[i][j]) {
        cout << "  [!] No road between " << c1 << " and " << c2
             << ". Add a road first (option 2).\n";
        return;
    }

    double b = readDouble("Enter the budget for the road (Billion RWF): ");
    budgets[i][j] = budgets[j][i] = b;
    cout << "Budget added successfully for the road between " << c1
         << " and " << c2 << ".\n";
}

// ════════════════════════════════════════════════════════════
//  MENU 4 — Edit / Update a City Name
// ════════════════════════════════════════════════════════════
void editCity() {
    if (numCities == 0) { cout << "  [!] No cities recorded yet.\n"; return; }

    int idx = readInt("Enter the index of the city to edit (1-" + to_string(numCities) + "): ");
    if (idx < 1 || idx > numCities) {
        cout << "  [!] Invalid index. Valid range: 1 to " << numCities << ".\n";
        return;
    }

    cout << "  Current name: " << cities[idx - 1] << "\n";
    string newName = readLine("Enter the new name for city: ");

    int existing = findByName(newName);
    if (existing != -1 && existing != idx - 1) {
        cout << "  [!] City '" << newName << "' already exists at index "
             << (existing + 1) << ".\n";
        return;
    }

    cities[idx - 1] = newName;
    cout << "City updated successfully.\n";
}

// ════════════════════════════════════════════════════════════
//  MENU 5 — Search for a City by Index
// ════════════════════════════════════════════════════════════
void searchCity() {
    if (numCities == 0) { cout << "  [!] No cities recorded yet.\n"; return; }

    int idx = readInt("Enter the index of the city to search (1-" + to_string(numCities) + "): ");
    if (idx < 1 || idx > numCities)
        cout << "  [!] No city found with index " << idx << ".\n";
    else
        cout << "  Found  ->  Index: " << idx << "  |  Name: " << cities[idx - 1] << "\n";
}

// ════════════════════════════════════════════════════════════
//  MENU 6 — Display Cities
// ════════════════════════════════════════════════════════════
void displayCities() {
    if (numCities == 0) { cout << "  No cities recorded yet.\n"; return; }
    cout << "\nCities:\n";
    for (int i = 0; i < numCities; i++)
        cout << (i + 1) << ". " << cities[i] << "\n";
}

// ════════════════════════════════════════════════════════════
//  MENU 7 — Display Roads Adjacency Matrix
// ════════════════════════════════════════════════════════════
void displayRoads() {
    displayCities();
    if (numCities == 0) return;

    cout << "\nRoads adjacency matrix:\n";
    for (int i = 0; i < numCities; i++) {
        for (int j = 0; j < numCities; j++) {
            cout << roads[i][j];
            if (j < numCities - 1) cout << " ";
        }
        cout << "\n";
    }
}

// ════════════════════════════════════════════════════════════
//  MENU 8 — Display All Data + Save to Files
// ════════════════════════════════════════════════════════════
void displayAll() {
    displayCities();
    if (numCities == 0) return;

    cout << "\nRoads adjacency matrix:\n";
    for (int i = 0; i < numCities; i++) {
        for (int j = 0; j < numCities; j++) {
            cout << roads[i][j];
            if (j < numCities - 1) cout << " ";
        }
        cout << "\n";
    }

    cout << "\nBudget adjacency matrix:\n";
    for (int i = 0; i < numCities; i++) {
        for (int j = 0; j < numCities; j++) {
            cout << fixed << setprecision(1) << budgets[i][j];
            if (j < numCities - 1) cout << "  ";
        }
        cout << "\n";
    }
}

void saveToFiles() {
    // ── cities.txt ──────────────────────────────────────────
    ofstream cf("cities.txt");
    cf << left << setw(8) << "Index" << "City_Name\n";
    for (int i = 0; i < numCities; i++)
        cf << left << setw(8) << (i + 1) << cities[i] << "\n";
    cf.close();

    // ── roads.txt ───────────────────────────────────────────
    ofstream rf("roads.txt");
    rf << left << setw(5) << "Nbr" << setw(26) << "Road" << "Budget\n";
    int num = 1;
    for (int i = 0; i < numCities; i++)
        for (int j = i + 1; j < numCities; j++)
            if (roads[i][j])
                rf << left
                   << setw(5)  << (to_string(num++) + ".")
                   << setw(26) << (cities[i] + "-" + cities[j])
                   << fixed << setprecision(2) << budgets[i][j] << "\n";
    rf.close();

    cout << "\nData saved successfully to cities.txt and roads.txt.\n";
}

// ════════════════════════════════════════════════════════════
//  MENU DISPLAY
// ════════════════════════════════════════════════════════════
void showMenu() {
    cout << "\n============================================\n";
    cout << "   Rwanda Infrastructure Management System\n";
    cout << "============================================\n";
    cout << "1. Add new city(ies)\n";
    cout << "2. Add roads between cities\n";
    cout << "3. Add the budget for roads\n";
    cout << "4. Edit city\n";
    cout << "5. Search for a city using its index\n";
    cout << "6. Display cities\n";
    cout << "7. Display roads\n";
    cout << "8. Display recorded data on console\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

// ════════════════════════════════════════════════════════════
//  MAIN
// ════════════════════════════════════════════════════════════
int main() {
    initArrays();

    int choice;
    do {
        showMenu();

        // Safely read menu choice
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [!] Please enter a number (1-9): ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: addCities();    break;
            case 2: addRoad();      break;
            case 3: addBudget();    break;
            case 4: editCity();     break;
            case 5: searchCity();   break;
            case 6: displayCities();  break;
            case 7: displayRoads();   break;
            case 8: displayAll(); saveToFiles(); break;
            case 9: cout << "\nExiting the application. Goodbye!\n"; break;
            default:
                cout << "  [!] Invalid choice. Please enter a number between 1 and 9.\n";
        }
    } while (choice != 9);

    return 0;
}
