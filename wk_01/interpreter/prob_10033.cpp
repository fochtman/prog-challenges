/* 
    AUTHOR  : TYLER FOCHTMAN
    PROBLEM : 10033
*/

#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int M = 1000;

int main() {
    int cases;
    cin >> cases;

    for (int i = 0; i < cases; i++) {
        if (i == 0) {
            string blankline;
            getline(cin, blankline);
            getline(cin, blankline);
        }

        vector<int> reg(10, 0);
        vector< vector<int>> ram(1000, {0, 0, 0});

        int j;
        int k = 0;
        string line;
        while (getline(cin, line)) {
            if (line.empty()) break;
            istringstream iss(line);
            while (iss >> j) {
                vector<int> xs({(j / 100) % 10, (j / 10) % 10, j % 10});
                ram[k] = xs;
                k++;
            }
        }

        int it    = 0;
        int count = 0;
        bool halt = false;
        while (!halt) {
            vector<int> ins = ram[it];
            int first       = ins[0];
            int d           = ins[1];
            int n           = ins[2];
            int s           = ins[2];
            int a           = ins[2];

            switch (first) {
                case 1: halt   = true;
                        break;
                case 2: reg[d] = n;
                        break;
                case 3: reg[d] = (reg[d] + n) % M;
                        break;
                case 4: reg[d] = (reg[d] * n) % M;
                        break;
                case 5: reg[d] = reg[s];
                        break;
                case 6: reg[d] = (reg[d] + reg[s]) % M;
                        break;
                case 7: reg[d] = (reg[d] * reg[s]) % M;
                        break;
                case 8: reg[d] = (ram[reg[a]][0] * 100) + (ram[reg[a]][1] * 10) + ram[reg[a]][2];
                        break;
                case 9: { 
                          int x = reg[ins[1]];
                          vector<int> xx({(x / 100) % 10, (x / 10) % 10, x % 10});
                          ram[reg[ins[2]]] = xx;
                        }
                        break;
                case 0: if (reg[s] != 0) it = reg[d] - 1;
                        break;
            }
            it = (it + 1) % M;
            count++;
        }
        cout << count << endl;
        if (i < cases - 1) cout << endl;
    }
    return 0;
}
