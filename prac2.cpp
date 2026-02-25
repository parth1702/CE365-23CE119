#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int inputCount;
    cout << "Number of input symbols: ";
    cin >> inputCount;

    vector<char> symbols(inputCount);
    cout << "Input symbols: ";
    for (int i = 0; i < inputCount; i++) {
        cin >> symbols[i];
    }

    int stateCount;
    cout << "Enter number of states: ";
    cin >> stateCount;

    int startState;
    cout << "Initial state: ";
    cin >> startState;
    startState--; // convert to 0-based

    int finalCount;
    cout << "Number of accepting states: ";
    cin >> finalCount;

    vector<int> finalStates(finalCount);
    cout << "Accepting states: ";
    for (int i = 0; i < finalCount; i++) {
        cin >> finalStates[i];
        finalStates[i]--; // convert to 0-based
    }

    vector<vector<int>> transition(stateCount, vector<int>(inputCount));

    cout << "Transition table:\n";
    for (int i = 0; i < stateCount; i++) {
        for (int j = 0; j < inputCount; j++) {
            cout << (i + 1) << " to " << symbols[j] << " -> ";
            cin >> transition[i][j];
            transition[i][j]--; // convert to 0-based
        }
    }

    string inputString;
    cout << "Input string: ";
    cin >> inputString;

    int currentState = startState;

    for (char ch : inputString) {
        int symbolIndex = -1;

        for (int i = 0; i < inputCount; i++) {
            if (symbols[i] == ch) {
                symbolIndex = i;
                break;
            }
        }

        if (symbolIndex == -1) {
            cout << "Invalid String\n";
            cout << "Made by Parth Prajapati - 23CE119\n";
            return 0;
        }

        currentState = transition[currentState][symbolIndex];
    }

    bool accepted = false;
    for (int state : finalStates) {
        if (currentState == state) {
            accepted = true;
            break;
        }
    }

    if (accepted)
        cout << "Valid String\n";
    else
        cout << "Invalid String\n";

    cout << "Made by Parth Prajapati - 23CE119\n";
    return 0;
}

