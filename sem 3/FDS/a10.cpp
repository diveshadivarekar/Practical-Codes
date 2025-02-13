#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>
#include <unordered_map>

using namespace std;

// Function to determine the precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to check if the character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to convert infix expression to postfix expression
string infixToPostfix(const string& infix) {
    stack<char> opStack;
    string postfix;

    for (char ch : infix) {
        if (isalnum(ch)) {
            postfix += ch; // Append operands to postfix
        } else if (isOperator(ch)) {
            while (!opStack.empty() && precedence(opStack.top()) >= precedence(ch)) {
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(ch); // Push current operator to stack
        }
    }

    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }

    return postfix;
}

// Function to evaluate postfix expression
int evaluatePostfix(const string& postfix, const unordered_map<char, int>& values) {
    stack<int> valueStack;

    for (char ch : postfix) {
        if (isalnum(ch)) {
            valueStack.push(values.at(ch)); // Get the value of the operand
        } else if (isOperator(ch)) {
            int right = valueStack.top(); valueStack.pop();
            int left = valueStack.top(); valueStack.pop();
            switch (ch) {
                case '+': valueStack.push(left + right); break;
                case '-': valueStack.push(left - right); break;
                case '*': valueStack.push(left * right); break;
                case '/': valueStack.push(left / right); break;
            }
        }
    }

    return valueStack.top(); // The final result
}

int main() {
    string infixExpression;

    // Input infix expression
    cout << "Enter an infix expression (e.g., a+b*c): ";
    getline(cin, infixExpression);

    // Define the values for the operands
    unordered_map<char, int> values;
    char operand;
    int value;

    // Input values for each operand
    cout << "Enter values for the operands (e.g., a=1 b=2 c=3): " << endl;
    while (true) {
        cout << "Operand (enter 'x' to finish): ";
        cin >> operand;
        if (operand == 'x') break; // Exit if 'x' is entered
        cout << "Value for " << operand << ": ";
        cin >> value;
        values[operand] = value; // Store the operand value
    }

    // Convert infix to postfix
    string postfixExpression = infixToPostfix(infixExpression);
    cout << "Postfix expression: " << postfixExpression << endl;

    // Evaluate postfix expression
    int result = evaluatePostfix(postfixExpression, values);
    cout << "Evaluation result: " << result << endl;

    return 0;
}
