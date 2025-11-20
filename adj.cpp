#include <iostream>
using namespace std;

#define MAX 100  // Maximum number of cities

// Adjacency Matrix Representation
class GraphMatrix {
public:
    int matrix[MAX][MAX] = {0};  // Matrix initialized to 0
    string cities[MAX];    // Array to store city names
    int vertices;

    GraphMatrix(int v) {
        vertices = v;
        for (int i = 0; i < v; i++) cities[i] = "";  // Initialize city names
    }

    int getCityIndex(string city) {
        for (int i = 0; i < vertices; i++) {
            if (cities[i] == city) return i; // If city exists, return index
        }
        for (int i = 0; i < vertices; i++) {
            if (cities[i] == "") {  // Store new city in the first empty slot
                cities[i] = city;
                return i;
            }
        }
        return -1; 
    }

    void addEdge(string u, string v, int cost) {
        int i = getCityIndex(u);
        int j = getCityIndex(v);
        matrix[i][j] = cost;
        matrix[j][i] = cost;
    }

    void display() {
        cout << "\nAdjacency Matrix:\n\n";

        // Print column headers (City names)
        cout << "   "; // Space for row headers
        for (int i = 0; i < vertices; i++) {
            cout << cities[i] << "\t ";
        }
        cout << endl;

        // Print matrix with row headers
        for (int i = 0; i < vertices; i++) {
            cout << cities[i] << " "; // Row header (City name)
            for (int j = 0; j < vertices; j++) {
                cout << matrix[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

// Node structure for adjacency list
struct Node {
    int cityIndex, cost;
    Node* next;
};

// Adjacency List Representation
class GraphList {
public:
    Node* adjList[MAX];  // Array of pointers to linked lists
    string cities[MAX];
    int vertices;

    GraphList(int v) {
        vertices = v;
        for (int i = 0; i < v; i++) {
            cities[i] = "";
            adjList[i] = nullptr;
        }
    }

    int getCityIndex(string city) {
        for (int i = 0; i < vertices; i++) {
            if (cities[i] == city) return i;
        }
        for (int i = 0; i < vertices; i++) {
            if (cities[i] == "") {  
                cities[i] = city;
                return i;
            }
        }
        return -1; 
    }

    void addEdge(string u, string v, int cost) {
        int i = getCityIndex(u);
        int j = getCityIndex(v);

        Node* newNode1 = new Node{j, cost, adjList[i]};
        adjList[i] = newNode1;

        Node* newNode2 = new Node{i, cost, adjList[j]};
        adjList[j] = newNode2;
    }

    void display() {
        cout << "\nAdjacency List:\n";
        for (int i = 0; i < vertices; i++) {
            if (cities[i] == "") continue;
            cout << cities[i] << " -> ";
            Node* temp = adjList[i];
            while (temp) {
                cout << "(" << cities[temp->cityIndex] << ", " << temp->cost << ") -> ";
                temp = temp->next;
            }
            cout << "NULL\n";
        }
    }

};

// Main function
int main() {
    int edges, cost;
    string u, v;
    
    cout << "Enter number of cities: ";
    int cities;
    cin >> cities;

    GraphMatrix gMatrix(cities);
    GraphList gList(cities);

    cout << "Enter number of flight paths: ";
    cin >> edges;

    cout << "Enter flight paths (City1 City2 Cost):\n";
    for (int i = 0; i < edges; i++) {
        cin >> u >> v >> cost;
        gMatrix.addEdge(u, v, cost);
        gList.addEdge(u, v, cost);
    }

    // Display both representations
    gMatrix.display();
    gList.display();

    return 0;
}