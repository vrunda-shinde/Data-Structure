#include <iostream>
#include <climits> // For INT_MAX
#include <string>

using namespace std;

class Network {
public:
    int nodes;
    int adjacencyMatrix[100][100]; // Adjacency matrix
    string deviceNames[100]; // Stores device names
    int totalCost = 0; // Total cost of MST

    Network(int x) {
        nodes = x;
        // Initialize adjacency matrix
        for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++) {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    // Function to add a connection
    void addConnection(int u, int v, int cost) {
        adjacencyMatrix[u][v] = cost;
        adjacencyMatrix[v][u] = cost;
    }

    // Function to display adjacency matrix
    void display() {
        cout << "\nAdjacency Matrix:\n";
        for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++) {
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Prim's Algorithm to find MST
    void prims() {
        int parent[100]; // Stores MST
        int key[100]; // Stores min weight edge
        int visited[100]; // Tracks visited nodes (0 = not visited, 1 = visited)

        for (int i = 0; i < nodes; i++) {
            key[i] = INT_MAX;
            visited[i] = 0;
        }

        key[0] = 0; // Start from first node
        parent[0] = -1; // Root of MST

        for (int count = 0; count < nodes - 1; count++) {
            int minVal = INT_MAX, u;

            // Find minimum key node
            for (int j = 0; j < nodes; j++) {
                if (visited[j] == 0 && key[j] < minVal) {
                    minVal = key[j];
                    u = j;
                }
            }

            visited[u] = 1; // Mark node as visited

            // Update key & parent of adjacent nodes
            for (int j = 0; j < nodes; j++) {
                if (adjacencyMatrix[u][j] && visited[j] == 0 && adjacencyMatrix[u][j] < key[j]) {
                    parent[j] = u;
                    key[j] = adjacencyMatrix[u][j];
                }
            }
        }

        // Display MST connections
        cout << "\nConnections in Minimum Spanning Tree (MST):\n";
        for (int i = 1; i < nodes; i++) {
            cout << deviceNames[parent[i]] << " - " << deviceNames[i] << "  Cost: " << adjacencyMatrix[i][parent[i]] << endl;
            totalCost += adjacencyMatrix[i][parent[i]];
        }
        cout << "Total Cost of MST: " << totalCost << endl;
    }
};

// Main function
int main() {
    int n;
    cout << "Enter number of network devices: ";
    cin >> n;

    Network net(n);

    // Input device names
    cout << "Enter the names of the devices:\n";
    for (int i = 0; i < n; i++) {
        cout << "Device " << i + 1 << ": ";
        cin >> net.deviceNames[i];
    }

    // Input link costs between devices
    cout << "\nEnter link costs between devices (Enter 0 if no direct link exists):\n";
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int cost;
            cout << "Cost between " << net.deviceNames[i] << " and " << net.deviceNames[j] << ": ";
            cin >> cost;
            net.addConnection(i, j, cost);
        }
    }

    // Display adjacency matrix
    net.display();

    // Compute and display MST using Prim's Algorithm
    net.prims();

    return 0;
}
