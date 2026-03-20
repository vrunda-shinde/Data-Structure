#include <iostream>
#include <string>
using namespace std;

const int MAX_SIZE = 100;

class MedicalRecord {
public:
    string name;
    string history;
    string treatment;

    MedicalRecord() : name(""), history(""), treatment("") {}

    MedicalRecord(string pname, string phistory, string ptreatment)
        : name(pname), history(phistory), treatment(ptreatment) {}
};

class MedicalRecordSystem {
private:
    MedicalRecord records[MAX_SIZE];
    int status[MAX_SIZE]; // 1 = occupied, 0 = empty, -2 = deleted
    int size;

    int hashFunction(string key) {
        int sum = 0;
        for (char c : key) sum += c;
        return sum % size;
    }

public:
    MedicalRecordSystem(int s = 10) {
        size = s;
        for (int i = 0; i < size; i++)
            status[i] = 0;
    }

    void addRecord(string name, string history, string treatment) {
        int index = hashFunction(name);
        for (int i = 0; i < size; i++) {
            int probeIndex = (index + i * i) % size;
            if (status[probeIndex] == 0 || status[probeIndex] == -2) {
                records[probeIndex] = MedicalRecord(name, history, treatment);
                status[probeIndex] = 1;
                cout << "Record added at index " << probeIndex << endl;
                return;
            }
        }
        cout << "Hash table is full. Cannot add record.\n";
    }

    void findRecord(string name) {
        int index = hashFunction(name);
        for (int i = 0; i < size; i++) {
            int probeIndex = (index + i * i) % size;
            if (status[probeIndex] == 1 && records[probeIndex].name == name) {
                cout << "Found at index " << probeIndex << ": " << records[probeIndex].name
                     << ", History: " << records[probeIndex].history
                     << ", Treatment: " << records[probeIndex].treatment << endl;
                return;
            }
        }
        cout << "Record not found.\n";
    }

    void updateRecord(string name) {
        int index = hashFunction(name);
        for (int i = 0; i < size; i++) {
            int probeIndex = (index + i * i) % size;
            if (status[probeIndex] == 1 && records[probeIndex].name == name) {
                string newHistory, newTreatment;
                cout << "Enter updated history: ";
                cin >> newHistory;
                cout << "Enter updated treatment: ";
                cin >> newTreatment;
                records[probeIndex].history = newHistory;
                records[probeIndex].treatment = newTreatment;
                cout << "Record updated.\n";
                return;
            }
        }
        cout << "Record not found.\n";
    }

    void deleteRecord(string name) {
        int index = hashFunction(name);
        for (int i = 0; i < size; i++) {
            int probeIndex = (index + i * i) % size;
            if (status[probeIndex] == 1 && records[probeIndex].name == name) {
                status[probeIndex] = -2;
                cout << "Record deleted.\n";
                return;
            }
        }
        cout << "Record not found.\n";
    }

    void displayAll() {
        for (int i = 0; i < size; i++) {
            if (status[i] == 1) {
                cout << "Index " << i << ": " << records[i].name
                     << ", History: " << records[i].history
                     << ", Treatment: " << records[i].treatment << endl;
            }
        }
    }
};

// Main function
int main() {
    MedicalRecordSystem system;
    int choice;

    do {
        cout << "\nMenu:\n"
             << "1. Add Record\n2. Find Record\n3. Update Record\n"
             << "4. Delete Record\n5. Display All\n6. Exit\nChoice: ";
        cin >> choice;

        string name, history, treatment;

        switch (choice) {
            case 1:
                cout << "Enter patient name: ";
                cin >> name;
                cout << "Enter medical history: ";
                cin >> history;
                cout << "Enter treatment plan: ";
                cin >> treatment;
                system.addRecord(name, history, treatment);
                break;

            case 2:
                cout << "Enter name to find: ";
                cin >> name;
                system.findRecord(name);
                break;

            case 3:
                cout << "Enter name to update: ";
                cin >> name;
                system.updateRecord(name);
                break;

            case 4:
                cout << "Enter name to delete: ";
                cin >> name;
                system.deleteRecord(name);
                break;

            case 5:
                system.displayAll();
                break;

            case 6:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}
