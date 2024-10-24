#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>
#include <string>
#include <map>
#include <cstdlib>
#include <vector>

using namespace std;

// Function to return precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to perform arithmetic operations
float applyOp(float a, float b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

// Function to check if string is a number
bool isNumber(const string &s) {
    return !s.empty() && (isdigit(s[0]) || s[0] == '.' || (s[0] == '-' && s.length() > 1));
}

// Function to convert infix expression to postfix
string infixToPostfix(const string &infix, bool &error, bool &missingOperand, bool &mismatchedParenthesis) {
    stringstream ss(infix), output;
    stack<char> ops;
    string token;
    error = false;
    missingOperand = false;
    mismatchedParenthesis = false;
    int openParen = 0, closeParen = 0;
    bool lastWasOperator = true;  // Helps to check consecutive operators

    while (ss >> token) {
        if (isNumber(token) || isalpha(token[0])) {
            output << token << " ";
            lastWasOperator = false;
        } else if (token == "(") {
            ops.push('(');
            openParen++;
            lastWasOperator = true;
        } else if (token == ")") {
            closeParen++;
            while (!ops.empty() && ops.top() != '(') {
                output << ops.top() << " ";
                ops.pop();
            }
            if (!ops.empty()) ops.pop();
            else {
                mismatchedParenthesis = true;
                return "";
            }
            lastWasOperator = false;
        } else {  // This should be an operator
            if (lastWasOperator) {  // If last was operator or start, it's an error
                missingOperand = true;
                return "";
            }
            while (!ops.empty() && precedence(ops.top()) >= precedence(token[0])) {
                output << ops.top() << " ";
                ops.pop();
            }
            ops.push(token[0]);
            lastWasOperator = true;
        }
    }

    if (lastWasOperator) {  // Ends with an operator, error
        missingOperand = true;
        return "";
    }

    while (!ops.empty()) {
        if (ops.top() == '(') {
            mismatchedParenthesis = true;
            return "";
        }
        output << ops.top() << " ";
        ops.pop();
    }

    if (openParen != closeParen) {
        mismatchedParenthesis = true;
    }

    return output.str();
}

// Function to evaluate postfix expression
float evaluatePostfix(const string &postfix, bool &error, bool hasVariable) {
    stringstream ss(postfix);
    stack<float> operands;
    string token;
    error = false;

    while (ss >> token) {
        if (isNumber(token)) {
            operands.push(stof(token));
        } else if (isalpha(token[0])) {
            hasVariable = true;
            return 0; // Do not evaluate if variables are present
        } else {  // This is an operator
            if (operands.size() < 2) {
                error = true;
                return 0;
            }
            float b = operands.top(); operands.pop();
            float a = operands.top(); operands.pop();
            operands.push(applyOp(a, b, token[0]));
        }
    }

    if (operands.size() != 1) {
        error = true;
        return 0;
    }

    return operands.top();
}
int main() {
    string infix;
    bool error = false, missingOperand = false, mismatchedParenthesis = false;

    int i = 0;

    while (true) {
        cout << "Enter infix expression (\"exit\" to quit): ";
        getline(cin, infix);
        if (infix == "exit") break;

        // Convert infix to postfix
        string postfix = infixToPostfix(infix, error, missingOperand, mismatchedParenthesis);
        
        if (mismatchedParenthesis) {
            cout << "Error: Infix expression: " << infix << " has mismatched parens!\n";
            continue;
        }
        if (missingOperand) {
            cout << "Error: Missing operands in the expression\n";
            i++;
            if (i == 4) break;
        }

        cout << "Postfix expression: " << postfix << endl;

        // Evaluate postfix
        bool evaluationError = false;
        bool hasVariable = false;
        float result = evaluatePostfix(postfix, evaluationError, hasVariable);

        if (hasVariable) {
            cout << "Postfix evaluation: " << postfix << " = " << postfix << endl;
        } else if (!evaluationError) {
            cout << "Postfix evaluation: " << postfix << " = " << result << endl;
        } else {
            cout << "Error: Missing operand in postfix string. Unable to evaluate postfix string!\n";
        }
    }

    return 0;
}

