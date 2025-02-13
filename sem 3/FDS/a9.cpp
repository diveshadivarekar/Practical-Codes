#include <iostream>
#include <stack>
#include <cctype>
#include <string>

using namespace std;

// Function to remove punctuation, spaces, and convert to lowercase
string preprocessString(const string& str) {
    string processed;
    for (char ch : str) {
        if (isalnum(ch)) {
            processed += tolower(ch); // Keep only alphanumeric characters
        }
    }
    return processed;
}

// Function to print original string followed by reversed string using stack
void printReversedString(const string& str) {
    stack<char> charStack;
    
    // Push all characters of the original string to the stack
    for (char ch : str) {
        if (isalnum(ch)) {
            charStack.push(tolower(ch)); // Push only alphanumeric and in lowercase
        }
    }

    cout << "Original String: " << str << endl;
    cout << "Reversed String: ";

    // Pop characters from the stack to display the reversed string
    while (!charStack.empty()) {
        cout << charStack.top();
        charStack.pop();
    }
    cout << endl;
}

// Function to check whether the given string is a palindrome
bool isPalindrome(const string& str) {
    string processed = preprocessString(str);
    stack<char> charStack;

    // Push all characters of the processed string to the stack
    for (char ch : processed) {
        charStack.push(ch);
    }

    // Check if the string is a palindrome
    for (char ch : processed) {
        if (charStack.top() != ch) {
            return false; // Not a palindrome if characters do not match
        }
        charStack.pop(); // Remove the top element after comparison
    }
    return true; // It's a palindrome
}

int main() {
    string input;

    // Get user input
    cout << "Enter a string: ";
    getline(cin, input);

    // Print original and reversed string
    printReversedString(input);

    // Check if the string is a palindrome
    if (isPalindrome(input)) {
        cout << "The given string is a palindrome." << endl;
    } else {
        cout << "The given string is not a palindrome." << endl;
    }

    return 0;
}
