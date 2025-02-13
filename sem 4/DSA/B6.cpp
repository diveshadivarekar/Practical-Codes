#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }


    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    else {
        root->right = insert(root->right, value);
    }

    return root;
}

int height(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + max(height(root->left), height(root->right));
}

int findMin(Node* root) {
    while (root && root->left != nullptr) {
        root = root->left;
    }
    return root ? root->data : -1;
}

void swapChildren(Node* root) {
    if (root == nullptr) return;
    
    swap(root->left, root->right);
    
    swapChildren(root->left);
    swapChildren(root->right);
}

bool search(Node* root, int value) {
    if (root == nullptr) {
        return false; 
    }
    if (root->data == value) {
        return true; 
    }
    if (value < root->data) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

int main() {
    Node* root = nullptr;
    int n, value;

    cout << "Enter the number of nodes to insert: ";
    cin >> n;

    cout << "Enter " << n << " values to insert into the binary search tree:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> value;
        root = insert(root, value);
    }

    cout << "In-order traversal of the tree: ";
    inorder(root);
    cout << endl;

    cout << "Enter value to insert a new node: ";
    cin >> value;
    root = insert(root, value);
    cout << "In-order after insertion: ";
    inorder(root);
    cout << endl;

    cout << "Height of the tree (longest path): " << height(root) << endl;

    cout << "Minimum value in the tree: " << findMin(root) << endl;

    cout << "Swapping left and right pointers at every node..." << endl;
    swapChildren(root);
    cout << "In-order after swapping: ";
    inorder(root);
    cout << endl;

    cout << "Enter value to search in the tree: ";
    cin >> value;
    cout << "Searching for value " << value << ": " 
         << (search(root, value) ? "Found" : "Not Found") << endl;

    return 0;
}

