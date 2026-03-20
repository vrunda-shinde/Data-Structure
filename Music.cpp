#include <iostream>
#include <string>
using namespace std;

const int MAX_SIZE = 100;

class MusicTrack {
public:
    string name;
    string artist;
    int duration;

    MusicTrack() : name(""), artist(""), duration(0) {}

    MusicTrack(string name, string artist, int duration)
        : name(name), artist(artist), duration(duration) {}
};

class MusicLibrary {
private:
    MusicTrack tracks[MAX_SIZE];
    int status[MAX_SIZE]; // 1 = occupied, 0 = empty, -2 = deleted
    int size;

    int hashFunction(string key) {
        int sum = 0;
        for (char c : key)
            sum += c;
        return sum % size;
    }

public:
    MusicLibrary(int s) {
        size = s;
        for (int i = 0; i < size; i++)
            status[i] = 0;
    }

    void addTrack(string name, string artist, int duration)
     {
    int index = hashFunction(name);

    for (int i = 0; i < size; ++i) {
        int probeIndex = (index + i) % size;

        if (status[probeIndex] == 0 || status[probeIndex] == -2) {
            tracks[probeIndex] = MusicTrack(name, artist, duration);
            status[probeIndex] = 1;
            cout << "Track added at index " << probeIndex << endl;
            return;
        }
    }

    cout << "Library is full. Cannot add track.\n";
}


    void findTrack(string name) {
        int index = hashFunction(name);

        for (int i = 0; i < size; ++i) {
            int probeIndex = (index + i) % size;
            if (status[probeIndex] == 1 && tracks[probeIndex].name == name) {
                cout << "Found at index " << probeIndex << ": " << tracks[probeIndex].name
                     << " by " << tracks[probeIndex].artist << " (" << tracks[probeIndex].duration << "s)\n";
                return;
            }
        }

        cout << "Track not found.\n";
    }

    void updateTrack(string name) {
        int index = hashFunction(name);

        for (int i = 0; i < size; ++i) {
            int probeIndex = (index + i) % size;
            if (status[probeIndex] == 1 && tracks[probeIndex].name == name) {
                string newName, newArtist;
                int newDuration;
                cin.ignore();
                cout << "Enter new track name: ";
                getline(cin, newName);
                cout << "Enter new artist: ";
                getline(cin, newArtist);
                cout << "Enter new duration: ";
                cin >> newDuration;
                tracks[probeIndex] = MusicTrack(newName, newArtist, newDuration);
                cout << "Track updated.\n";
                return;
            }
        }

        cout << "Track not found.\n";
    }

    void deleteTrack(string name) {
        int index = hashFunction(name);

        for (int i = 0; i < size; ++i) {
            int probeIndex = (index + i) % size;
            if (status[probeIndex] == 1 && tracks[probeIndex].name == name) {
                status[probeIndex] = -2;
                cout << "Track deleted.\n";
                return;
            }
        }

        cout << "Track not found.\n";
    }

    void displayAll() {
        for (int i = 0; i < size; i++) {
            if (status[i] == 1) {
                cout << "Index " << i << ": " << tracks[i].name << " by "
                     << tracks[i].artist << " (" << tracks[i].duration << "s)\n";
            }
        }
    }
};

int main() {
    int size;
    cout << "Enter library size (1 to " << MAX_SIZE << "): ";
    cin >> size;

    if (size <= 0 || size > MAX_SIZE) {
        cout << "Invalid size.\n";
        return 1;
    }

    MusicLibrary lib(size);
    int choice;

    do {
        cout << "\nMenu:\n"
             << "1. Add Track\n"
             << "2. Find Track\n"
             << "3. Update Track\n"
             << "4. Delete Track\n"
             << "5. Display All Tracks\n"
             << "6. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        string name, artist;
        int duration;

        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1:
                cout << "Enter track name: ";
                getline(cin, name);
                cout << "Enter artist name: ";
                getline(cin, artist);
                cout << "Enter duration (in seconds): ";
                cin >> duration;
                lib.addTrack(name, artist, duration);
                break;

            case 2:
                cout << "Enter track name to find: ";
                getline(cin, name);
                lib.findTrack(name);
                break;

            case 3:
                cout << "Enter track name to update: ";
                getline(cin, name);
                lib.updateTrack(name);
                break;

            case 4:
                cout << "Enter track name to delete: ";
                getline(cin, name);
                lib.deleteTrack(name);
                break;

            case 5:
                lib.displayAll();
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
