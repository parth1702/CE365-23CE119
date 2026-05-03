#include <iostream>
#include <string>
#include <algorithm>
using namespace std;



string input;
int i = 0;

// Function declarations
bool S();
bool L();
bool Ldash();



// S -> ( L ) | a
bool S() {
    if (i < input.length() && input[i] == 'a') {
        i++;   
        return true;
    }
    else if (i < input.length() && input[i] == '(') {
        i++;   

        if (!L()) {
            return false;
        }

        if (i < input.length() && input[i] == ')') {
            i++;   
            return true;
        }
        else {
            return false;
        }
    }

    return false;
}

// L -> S L'
bool L() {
    if (!S()) {
        return false;
    }

    if (!Ldash()) {
        return false;
    }

    return true;
}

// L' -> , S L' | epsilon
bool Ldash() {
    if (i < input.length() && input[i] == ',') {
        i++;   

        if (!S()) {
            return false;
        }

        if (!Ldash()) {
            return false;
        }
    }

    // epsilon case
    return true;
}

int main() {
    
    cout << "Enter string: ";
    cin>>input;

    if (S() && i == input.length()) {
        cout << "Valid string" << endl;
    }
    else {
        cout << "Invalid string" << endl;
    }

    return 0;
}
