#include <iostream>
using namespace std;

class MaxHeap {
    int heap[100];
    int size;

public:
    MaxHeap() {
        size = 0;
    }

    void insert(int val) {
        int i = size;
        heap[size++] = val;

        while (i > 0 && heap[i] > heap[(i - 1) / 2]) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void deleteRoot() {
        if (size == 0) {
            cout << "Heap is empty!\n";
            return;
        }

        cout << "Deleted root: " << heap[0] << endl;
        heap[0] = heap[--size];

        int i = 0;
        while (2 * i + 1 < size) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (heap[left] > heap[largest])
                largest = left;
            if (right < size && heap[right] > heap[largest])
                largest = right;

            if (largest == i)
                break;

            swap(heap[i], heap[largest]);
            i = largest;
        }
    }

    void display() {
        for (int i = 0; i < size; i++)
            cout << heap[i] << " ";
        cout << endl;
    }
};

class MinHeap {
    int heap[100];
    int size;

public:
    MinHeap() {
        size = 0;
    }

    void insert(int val) {
        int i = size;
        heap[size++] = val;

        while (i > 0 && heap[i] < heap[(i - 1) / 2]) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void deleteRoot() {
        if (size == 0) {
            cout << "Heap is empty!\n";
            return;
        }

        cout << "Deleted root: " << heap[0] << endl;
        heap[0] = heap[--size];

        int i = 0;
        while (2 * i + 1 < size) {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (heap[left] < heap[smallest])
                smallest = left;
            if (right < size && heap[right] < heap[smallest])
                smallest = right;

            if (smallest == i)
                break;

            swap(heap[i], heap[smallest]);
            i = smallest;
        }
    }

    void display() {
        for (int i = 0; i < size; i++)
            cout << heap[i] << " ";
        cout << endl;
    }
};

int main() {
    int choice, n, val;

    cout << "Choose Heap Type:\n";
    cout << "1. Max Heap\n2. Min Heap\nEnter choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            MaxHeap h;
            cout << "Enter number of elements: ";
            cin >> n;

            cout << "Enter " << n << " elements:\n";
            for (int i = 0; i < n; i++) {
                cin >> val;
                h.insert(val);
            }

            cout << "\nMax Heap: ";
            h.display();

            h.deleteRoot();
            cout << "After deletion: ";
            h.display();
            break;
        }
        case 2: {
            MinHeap h;
            cout << "Enter number of elements: ";
            cin >> n;

            cout << "Enter " << n << " elements:\n";
            for (int i = 0; i < n; i++) {
                cin >> val;
                h.insert(val);
            }

            cout << "\nMin Heap: ";
            h.display();

            h.deleteRoot();
            cout << "After deletion: ";
            h.display();
            break;
        }
        default:
            cout << "Invalid choice!\n";
    }

    return 0;
}