#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    string keyword, meaning;
    int height;
    Node* left;
    Node* right;

    Node(string key, string mean) : keyword(key), meaning(mean), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    Node* root;

    int height(Node* node) { return node ? node->height : 0; }
    int balanceFactor(Node* node) { return node ? height(node->left) - height(node->right) : 0; }

    Node* rightRotate(Node* node) {
        Node* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        node->height = max(height(node->left), height(node->right)) + 1;
        newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
        return newRoot;
    }

    Node* leftRotate(Node* node) {     
        Node* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        node->height = max(height(node->left), height(node->right)) + 1;
        newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
        return newRoot;
    }

    Node* insert(Node* node, const string& keyword, const string& meaning) {
        if (!node) return new Node(keyword, meaning);
        if (keyword < node->keyword) node->left = insert(node->left, keyword, meaning);
        else if (keyword > node->keyword) node->right = insert(node->right, keyword, meaning);
        else node->meaning = meaning;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = balanceFactor(node);

        if (balance > 1 && keyword < node->left->keyword) return rightRotate(node);
        if (balance < -1 && keyword > node->right->keyword) return leftRotate(node);
        if (balance > 1 && keyword > node->left->keyword) { node->left = leftRotate(node->left); return rightRotate(node); }
        if (balance < -1 && keyword < node->right->keyword) { node->right = rightRotate(node->right); return leftRotate(node); }  

        return node;
    }

    Node* deleteNode(Node* root, const string& keyword) {
        if (!root) return root;
        if (keyword < root->keyword) root->left = deleteNode(root->left, keyword);
        else if (keyword > root->keyword) root->right = deleteNode(root->right, keyword);
        else {
            if (!root->left) { Node* temp = root->right; delete root; return temp; }
            if (!root->right) { Node* temp = root->left; delete root; return temp; }
            Node* temp = minNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = balanceFactor(root);
        if (balance > 1 && balanceFactor(root->left) >= 0) return rightRotate(root);
        if (balance < -1 && balanceFactor(root->right) <= 0) return leftRotate(root);
        if (balance > 1 && balanceFactor(root->left) < 0) { root->left = leftRotate(root->left); return rightRotate(root); }
        if (balance < -1 && balanceFactor(root->right) > 0) { root->right = rightRotate(root->right); return leftRotate(root); }

        return root;
    }

    Node* minNode(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    void inorder(Node* root) { 
        if (root) {
            inorder(root->left);
            cout << root->keyword << ": " << root->meaning << endl;
            inorder(root->right);
        }
    }

    void reverseInorder(Node* root) {
        if (root) {
            reverseInorder(root->right);
            cout << root->keyword << ": " << root->meaning << endl;
            reverseInorder(root->left);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const string& keyword, const string& meaning) {
        root = insert(root, keyword, meaning);
    }

    void deleteKeyword(const string& keyword) {
        root = deleteNode(root, keyword);
    }

    void updateKeyword(const string& keyword, const string& newMeaning) {
        Node* node = search(root, keyword);
        if (node) node->meaning = newMeaning;
        else cout << "Keyword not found!" << endl;
    }

    void displayAscending() { inorder(root); }
    void displayDescending() { reverseInorder(root); }

    int maxComparisons() { return height(root); }

    Node* search(Node* root, const string& keyword) {
        if (!root || root->keyword == keyword) return root;
        if (keyword < root->keyword) return search(root->left, keyword);
        return search(root->right, keyword);
    }
};

int main() {
    AVLTree dict;
    
    dict.insert("apple", "A fruit");
    dict.insert("banana", "Another fruit");
    dict.insert("cat", "An animal");
    dict.insert("dog", "Another animal");
    
    cout << "Dictionary in Ascending Order:\n";
    dict.displayAscending();
    
    cout << "\nDictionary in Descending Order:\n";
    dict.displayDescending();
    
    cout << "\nUpdating 'banana'...\n";
    dict.updateKeyword("banana", "A yellow fruit");
    
    cout << "\nDictionary after update:\n";
    dict.displayAscending();
    
    cout << "\nDeleting 'apple'...\n";
    dict.deleteKeyword("apple");
    
    cout << "\nDictionary after deletion:\n";
    dict.displayAscending();
    
    cout << "\nMaximum comparisons needed for search: " << dict.maxComparisons() << endl;

    return 0;
}
