#include <iostream>
#include <stack>
#include <sstream>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double applyOp(double a, double b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    return 0;
}

bool isNumber(string s) {
    for (char c : s) {
        if (!isdigit(c) && c != '.') return false;
    }
    return true;
}

string constantFold(string expr) {
    stack<string> values;
    stack<char> ops;

    for (int i = 0; i < expr.length(); i++) {

        if (expr[i] == ' ') continue;

        if (isalnum(expr[i]) || expr[i] == '.') {
            string val = "";
            while (i < expr.length() && (isalnum(expr[i]) || expr[i] == '.')) {
                val += expr[i];
                i++;
            }
            i--;
            values.push(val);
        }

        else if (expr[i] == '(') {
            ops.push(expr[i]);
        }

        else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                char op = ops.top(); ops.pop();

                string b = values.top(); values.pop();
                string a = values.top(); values.pop();

                if (isNumber(a) && isNumber(b)) {
                    double res = applyOp(stod(a), stod(b), op);
                    values.push(to_string((int)res));
                } else {
                    values.push(a + " " + op + " " + b);
                }
            }
            ops.pop();
        }

        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i])) {
                char op = ops.top(); ops.pop();

                string b = values.top(); values.pop();
                string a = values.top(); values.pop();

                if (isNumber(a) && isNumber(b)) {
                    double res = applyOp(stod(a), stod(b), op);
                    values.push(to_string((int)res));
                } else {
                    values.push(a + " " + op + " " + b);
                }
            }
            ops.push(expr[i]);
        }
    }

    while (!ops.empty()) {
        char op = ops.top(); ops.pop();

        string b = values.top(); values.pop();
        string a = values.top(); values.pop();

        if (isNumber(a) && isNumber(b)) {
            double res = applyOp(stod(a), stod(b), op);
            values.push(to_string((int)res));
        } else {
            values.push(a + " " + op + " " + b);
        }
    }

    return values.top();
}

int main() {
    string expr;
    cout << "Enter expression: ";
    getline(cin, expr);

    string result = constantFold(expr);

    cout << "\nOptimized Expression: " << result << endl;

    return 0;
}
