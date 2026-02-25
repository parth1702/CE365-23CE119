#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> FIRST, FOLLOW;
set<char> nonTerminals = {'S', 'A', 'B', 'C', 'D'};

/* Function to compute FIRST */
void computeFirst(char symbol) {
    // If already computed, skip
    if (!FIRST[symbol].empty()) return;

    for (string production : grammar[symbol]) {
        // If ε production
        if (production == "^") {
            FIRST[symbol].insert('^');
            continue;
        }

        for (int i = 0; i < production.length(); i++) {
            char curr = production[i];

            // If terminal
            if (nonTerminals.find(curr) == nonTerminals.end()) {
                FIRST[symbol].insert(curr);
                break;
            }

            // If non-terminal
            computeFirst(curr);

            bool epsilonFound = false;
            for (char ch : FIRST[curr]) {
                if (ch == '^')
                    epsilonFound = true;
                else
                    FIRST[symbol].insert(ch);
            }

            if (!epsilonFound)
                break;

            if (i == production.length() - 1)
                FIRST[symbol].insert('^');
        }
    }
}

/* Function to compute FOLLOW */
void computeFollow() {
    FOLLOW['S'].insert('$'); // Start symbol

    bool updated = true;
    while (updated) {
        updated = false;

        for (auto g : grammar) {
            char lhs = g.first;

            for (string prod : g.second) {
                for (int i = 0; i < prod.length(); i++) {
                    char curr = prod[i];

                    if (nonTerminals.find(curr) == nonTerminals.end())
                        continue;

                    bool epsilonNext = true;

                    for (int j = i + 1; j < prod.length(); j++) {
                        char next = prod[j];
                        epsilonNext = false;

                        if (nonTerminals.find(next) == nonTerminals.end()) {
                            if (FOLLOW[curr].insert(next).second)
                                updated = true;
                            break;
                        }

                        for (char ch : FIRST[next]) {
                            if (ch != '^')
                                if (FOLLOW[curr].insert(ch).second)
                                    updated = true;
                        }

                        if (FIRST[next].count('^') == 0)
                            break;
                        else
                            epsilonNext = true;
                    }

                    if (epsilonNext) {
                        for (char ch : FOLLOW[lhs]) {
                            if (FOLLOW[curr].insert(ch).second)
                                updated = true;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    // Grammar definition
    grammar['S'] = {"ABC", "D"};
    grammar['A'] = {"a", "^"};
    grammar['B'] = {"b", "^"};
    grammar['C'] = {"(S)", "c"};
    grammar['D'] = {"AC"};

    // Compute FIRST sets
    for (char nt : nonTerminals)
        computeFirst(nt);

    // Compute FOLLOW sets
    computeFollow();

    // Print FIRST
    for (char nt : nonTerminals) {
        cout << "First(" << nt << ") = {";
        for (char ch : FIRST[nt])
            cout << ch << " ";
        cout << "}" << endl;
    }

    cout << endl;

    // Print FOLLOW
    for (char nt : nonTerminals) {
        cout << "Follow(" << nt << ") = {";
        for (char ch : FOLLOW[nt])
            cout << ch << " ";
        cout << "}" << endl;
    }

    return 0;
}
