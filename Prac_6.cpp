#include <iostream>
#include <string>
using namespace std;

string s;
int i = 0;

bool S();
bool Ldash();
bool L();

bool S() {
    if (i < s.length() && isalpha(s[i])) {
        i++;    
        return true;
    }
    return false;
}

bool Ldash() {
    if (i < s.length() && s[i] == ',') {
        i++; 
        if (S()) {
            return Ldash();
        }
        return false;
    }
    return true;   
}

bool L() {
    if (S()) {
        return Ldash();
    }
    return false;
}

int main() {
    cout << "Enter input string: ";
    cin >> s;

    if (L() && i == s.length()) {
        cout << "String is valid.\n";
    } else {
        cout << "String is invalid.\n";
    }

    return 0;
}
