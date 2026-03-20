#include <iostream>
using namespace std;

const int INF = 9999;

class Graph {
public:
    int v;
    int m[100][100]; // Adjacency matrix

    Graph(int x) {
        v = x;
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                m[i][j] = 0; // No connection initially
            }
        }
    }

    // Add a bidirectional road (edge) between two locations
    void addEdge(int u, int v, int w) {
        m[u][v] = w;
        m[v][u] = w;
    }

    // Display the graph as adjacency matrix
    void display() {
        cout << "\nRoad Network (Adjacency Matrix):\n";
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                cout << m[i][j] << " ";
            }
            cout << endl;
        }
    }
};

// Dijkstra’s Algorithm to find shortest distance from start
void dijkstra(Graph& g, int start) {
    int distance[100], visited[100];

    for (int i = 0; i < g.v; i++) {
        distance[i] = INF;
        visited[i] = 0;
    }

    distance[start] = 0;
    int current = start;

    for (int count = 0; count < g.v - 1; count++) {
        visited[current] = 1;

        for (int j = 0; j < g.v; j++) {
            if (g.m[current][j] != 0 && visited[j] == 0) {
                int temp = distance[current] + g.m[current][j];
                if (distance[j] > temp) {
                    distance[j] = temp;
                }
            }
        }

        int min = INF;
        for (int j = 0; j < g.v; j++) {
            if (visited[j] == 0 && distance[j] < min) {
                min = distance[j];
                current = j;
            }
        }
    }

    // Output the distances from your location to each hall
    cout << "\nShortest Distance from Your Location to Each Hall:\n";
    for (int i = 0; i < g.v; i++) {
        if (i == start) continue; // Skip current location
        cout << "Marriage Hall " << i << " is " << distance[i] << " units away.\n";
    }
}

int main() {
    int V, E;
    cout << "Enter total number of locations (1 current location + number of halls): ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of roads (paths between locations): ";
    cin >> E;

    cout << "Enter road details (format: location1 location2 distance):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    g.display();

    int startNode;
    cout << "\nEnter your current location (node number): ";
    cin >> startNode;

    if (startNode >= 0 && startNode < V) {
        dijkstra(g, startNode);
    } else {
        cout << "Invalid start location!" << endl;
    }

    return 0;
}