#include <bits/stdc++.h>
using namespace std;

struct Event {
    int id;
    string name, date, time, type, location;
};

vector<Event> events;
bool isAdmin = false;
int nextId = 1;


void saveEventsToCSV() {
    ofstream file("events.csv");
    if (!file.is_open()) {
        cout << "[!] Could not open file for saving!\n";
        return;
    }

    file << "ID,Name,Date,Time,Type,Location\n";

    for (auto &e : events) {
        file << e.id << "," << e.name << "," << e.date << "," 
             << e.time << "," << e.type << "," << e.location << "\n";
    }

    file.close();
    cout << "[+] Events saved to events.csv\n";
}

void loadEventsFromCSV() {
    ifstream file("events.csv");
    if (!file.is_open()) return; 

    string line;
    getline(file, line); 
    while (getline(file, line)) {
        stringstream ss(line);
        Event e;
        string idStr;
        getline(ss, idStr, ',');
        e.id = stoi(idStr);
        getline(ss, e.name, ',');
        getline(ss, e.date, ',');
        getline(ss, e.time, ',');
        getline(ss, e.type, ',');
        getline(ss, e.location, ',');
        events.push_back(e);
        nextId = max(nextId, e.id + 1);
    }
    file.close();
}

void adminLogin() {
    string pass;
    cout << "Enter admin password: ";
    getline(cin, pass);
    if (pass == "admin123") {
        isAdmin = true;
        cout << "[+] Logged in as Admin!\n";
    } else {
        cout << "[!] Wrong password!\n";
    }
}
void addEvent() {
    if (!isAdmin) { cout << "[!] Only admin can add events.\n"; return; }

    Event e;
    e.id = nextId++;
    cout << "Enter name: "; getline(cin, e.name);
    cout << "Enter date (DD-MM-YYYY): "; getline(cin, e.date);
    cout << "Enter time (HH:MM): "; getline(cin, e.time);
    cout << "Enter type: "; getline(cin, e.type);
    cout << "Enter location: "; getline(cin, e.location);

    for (auto &ev : events) {
        if (ev.name == e.name && ev.date == e.date && ev.time == e.time) {
            cout << "[!] Duplicate event found!\n";
            return;
        }
    }

    events.push_back(e);
    cout << "[+] Event added successfully!\n";
    saveEventsToCSV();
}

void editEvent() {
    if (!isAdmin) { cout << "[!] Only admin can edit events.\n"; return; }

    int id; cout << "Enter event ID to edit: "; cin >> id; cin.ignore();
    for (auto &e : events) {
        if (e.id == id) {
            cout << "Editing event: " << e.name << "\n";
            cout << "Enter new name: "; getline(cin, e.name);
            cout << "Enter new date: "; getline(cin, e.date);
            cout << "Enter new time: "; getline(cin, e.time);
            cout << "Enter new type: "; getline(cin, e.type);
            cout << "Enter new location: "; getline(cin, e.location);
            cout << "[+] Event updated!\n";
            saveEventsToCSV();
            return;
        }
    }
    cout << "[!] Event not found!\n";
}

void deleteEvent() {
    if (!isAdmin) { cout << "[!] Only admin can delete events.\n"; return; }

    int id; cout << "Enter event ID to delete: "; cin >> id; cin.ignore();
    for (int i = 0; i < (int)events.size(); i++) {
        if (events[i].id == id) {
            cout << "[-] Deleted event: " << events[i].name << "\n";
            events.erase(events.begin() + i);
            saveEventsToCSV();
            return;
        }
    }
    cout << "[!] Event not found!\n";
}


void viewEvents() {
    if (events.empty()) { cout << "[!] No events scheduled.\n"; return; }
    cout << "\n--- All Events ---\n";
    for (auto &e : events) {
        cout << "ID: " << e.id << " | " << e.name << " | " << e.date << " " << e.time
             << " | " << e.type << " | " << e.location << "\n";
    }
}

void analyticsModule() {
    if (!isAdmin) { cout << "[!] Only admin can view analytics.\n"; return; }

    cout << "--- Event Analytics ---\n";
    cout << "Total events: " << events.size() << "\n";

    map<string, int> typeCount;
    for (auto &e : events) typeCount[e.type]++;
    cout << "Events by type:\n";
    for (auto &p : typeCount) cout << p.first << ": " << p.second << "\n";

    map<string, int> slotCount;
    for (auto &e : events) slotCount[e.date + " " + e.time]++;

    string commonSlot = "None";
    int maxCount = 0;
    for (auto &p : slotCount) {
        if (p.second > maxCount) {
            maxCount = p.second;
            commonSlot = p.first;
        }
    }
    cout << "Most common slot: " << commonSlot << " (" << maxCount << " times)\n";
}

void sendReminders() {
    if (!isAdmin) { cout << "[!] Only admin can send reminders.\n"; return; }
    cout << "Pretend: Reading attendee emails from Excel file and sending reminders...\n";
    for (auto &e : events) {
        cout << "Reminder sent for " << e.name << " on " << e.date << " " << e.time << "\n";
    }
}


int main() {
    loadEventsFromCSV(); 

    while (true) {
        cout << "\n==== Smart Event Manager ====";
        cout << "\n1. Admin Login";
        cout << "\n2. Add Event (Admin)";
        cout << "\n3. Edit Event (Admin)";
        cout << "\n4. Delete Event (Admin)";
        cout << "\n5. View Events";
        cout << "\n6. Analytics Module (Admin)";
        cout << "\n7. Send Reminders (Admin)";
        cout << "\n0. Exit";
        cout << "\nChoose option: ";

        int choice;
        cin >> choice; cin.ignore();

        switch (choice) {
            case 1: adminLogin(); break;
            case 2: addEvent(); break;
            case 3: editEvent(); break;
            case 4: deleteEvent(); break;
            case 5: viewEvents(); break;
            case 6: analyticsModule(); break;
            case 7: sendReminders(); break;
            case 0: cout << "Exiting...\n"; return 0;
            default: cout << "[!] Invalid option!\n";
        }
    }
}
