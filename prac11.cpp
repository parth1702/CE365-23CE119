#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
using namespace std;

int tempCount = 1;

string getTemp() {
    return "t" + to_string(tempCount++);
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

struct Quad {
    string op, arg1, arg2, result;
};

vector<Quad> quadruples;

string applyOperator(char op, string b, string a) {
    string temp = getTemp();
    quadruples.push_back({string(1, op), a, b, temp});
    return temp;
}

vector<Quad> generateQuadruple(string expr) {
    stack<string> values;
    stack<char> ops;

    for (int i = 0; i < expr.length(); i++) {

        if (expr[i] == ' ') continue;

        // Number (including multi-digit)
        if (isdigit(expr[i])) {
            string val = "";
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
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
                values.push(applyOperator(op, b, a));
            }
            ops.pop();
        }

        else { // operator
            while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i])) {
                char op = ops.top(); ops.pop();
                string b = values.top(); values.pop();
                string a = values.top(); values.pop();
                values.push(applyOperator(op, b, a));
            }
            ops.push(expr[i]);
        }
    }

    while (!ops.empty()) {
        char op = ops.top(); ops.pop();
        string b = values.top(); values.pop();
        string a = values.top(); values.pop();
        values.push(applyOperator(op, b, a));
    }

    return quadruples;
}

int main() {
    string expr;
    cout << "Enter expression: ";
    getline(cin, expr);

    vector<Quad> result = generateQuadruple(expr);

    cout << "\nOperator\tOperand1\tOperand2\tResult\n";
    for (auto q : result) {
        cout << q.op << "\t\t" << q.arg1 << "\t\t" << q.arg2 << "\t\t" << q.result << endl;
    }

    return 0;
}
