#include <iostream>
#include <stack>
using namespace std;

// Get precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Convert infix to postfix
string infixToPostfix(string infix) {
    stack<char> s;
    string postfix = "";

    for (char ch : infix) {
        if (isdigit(ch)) {
            postfix += ch; // number → add to postfix
        } 
        else if (ch == '(') {
            s.push(ch);
        } 
        else if (ch == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop(); // remove '('
        } 
        else { // operator
            while (!s.empty() && precedence(s.top()) >= precedence(ch)) {
                postfix += s.top();
                s.pop();
            }
            s.push(ch);
        }
    }

    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}

// Evaluate postfix expression
int evaluatePostfix(string postfix) {
    stack<int> s;

    for (char ch : postfix) {
        if (isdigit(ch)) {
            s.push(ch - '0'); // char → int
        } else {
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            if (ch == '+') s.push(a + b);
            if (ch == '-') s.push(a - b);
            if (ch == '*') s.push(a * b);
            if (ch == '/') s.push(a / b);
        }
    }

    return s.top();
}

int main() {
    string infix;
    cout << "Enter expression (single-digit numbers only): ";
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;

    int result = evaluatePostfix(postfix);
    cout << "Result: " << result << endl;

    return 0;
}
