#include <iostream>
#include <string>
using namespace std;

//  Binary Tree Node Structure
class Node {
public:
    string data;
    Node *left, *right;

    Node(string val) {
        data = val;
        left = right = NULL;
    }
};

//  Insert a node into the binary tree
void insert(Node *&root, string val) {
    if (root == NULL) {
        root = new Node(val);
        return;
    }

    char choice;
    cout << "Insert left (L) or right (R) of " << root->data << "? ";
    cin >> choice;

    if (choice == 'L' || choice == 'l') {
        if (root->left == NULL)
            root->left = new Node(val);
        else
            insert(root->left, val);
    } else {
        if (root->right == NULL)
            root->right = new Node(val);
        else
            insert(root->right, val);
    }
}

//  Recursive Preorder Traversal
void preorder(Node *root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// 🌿 Recursive Inorder Traversal
void inorder(Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

//  Recursive Postorder Traversal
void postorder(Node *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

//  Count total nodes in the tree
int countNodes(Node *root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

//  Count and print all leaf nodes
int countLeafNodes(Node *root) {
    if (root == NULL) return 0;

    if (root->left == NULL && root->right == NULL) {
        cout << root->data << " "; // Print leaf node
        return 1;
    }

    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

//  Find tree height
int treeHeight(Node *root) {
    if (root == NULL) return 0;
    return 1 + max(treeHeight(root->left), treeHeight(root->right));
}

//  Find and print ancestors of a node
bool findAncestors(Node *root, string target) {
    if (root == NULL) return false;
    if (root->data == target) return true;

    if (findAncestors(root->left, target) || findAncestors(root->right, target)) {
        cout << root->data << " ";
        return true;
    }
    return false;
}

//  Update a node's value (uses global flag)
bool updated = false;

void updateNode(Node *root, string oldVal, string newVal) {
    if (root == NULL) return;

    if (root->data == oldVal) {
        root->data = newVal;
        updated = true;
        return;
    }

    updateNode(root->left, oldVal, newVal);
    updateNode(root->right, oldVal, newVal);
}

int main() {
    Node *root = NULL;
    int choice;
    string val, target;

    do {
        cout << "\n------ MENU ------\n";
        cout << "1. Create Root\n2. Insert Node\n3. Preorder Traversal\n4. Inorder Traversal\n5. Postorder Traversal\n";
        cout << "6. Count Total Nodes\n7. Count & Print Leaf Nodes\n8. Tree Height\n9. Find Ancestors\n";
        cout << "10. Exit\n11. Update Node Value\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (root == NULL) {
                cout << "Enter root node value: ";
                cin >> val;
                root = new Node(val);
            } else {
                cout << "Root already exists!\n";
            }
            break;

        case 2:
            if (root == NULL) {
                cout << "Create a root first!\n";
            } else {
                cout << "Enter node value: ";
                cin >> val;
                insert(root, val);
            }
            break;

        case 3:
            cout << "Preorder Traversal: ";
            preorder(root);
            cout << endl;
            break;

        case 4:
            cout << "Inorder Traversal: ";
            inorder(root);
            cout << endl;
            break;

        case 5:
            cout << "Postorder Traversal: ";
            postorder(root);
            cout << endl;
            break;

        case 6:
            cout << "Total Nodes: " << countNodes(root) << endl;
            break;

        case 7:
            cout << "Leaf Nodes: ";
            cout << "\nTotal Leaf Nodes: " << countLeafNodes(root) << endl;
            break;

        case 8:
            cout << "Tree Height: " << treeHeight(root) << endl;
            break;

        case 9:
            cout << "Enter node to find ancestors: ";
            cin >> target;
            cout << "Ancestors of " << target << ": ";
            if (!findAncestors(root, target))
                cout << "No ancestors found.";
            cout << endl;
            break;

        case 10:
            cout << "Exiting program...\n";
            break;

        case 11:
            if (root == NULL) {
                cout << "Tree is empty!\n";
            } else {
                cout << "Enter value to update: ";
                cin >> val;
                cout << "Enter new value: ";
                cin >> target;
                updated = false;
                updateNode(root, val, target);
                if (!updated)
                    cout << "Node not found.\n";
            }
            break;

        default:
            cout << "Invalid input! Try again.\n";
            break;
        }
    } while (choice != 11);

    return 0;
}