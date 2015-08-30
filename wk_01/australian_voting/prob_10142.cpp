/* 
    AUTHOR  : TYLER FOCHTMAN
    PROBLEM : 10142
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <limits.h>

using namespace std;

int main() {
    int cases;
    cin >> cases;

    for (int i = 0; i < cases; i++) {
        int n;
        cin >> n;

        string blankline;
        getline(cin, blankline);

        vector<string> candidates(n);
        for (string& c: candidates) getline(cin, c);

        vector< vector<int>> ballots;
        string votes;
        while (getline(cin, votes)) {
            if (votes.empty()) break;
            vector<int> b;
            istringstream iss(votes);
            int j;
            while (iss >> j) b.push_back(j - 1);
            ballots.push_back(b);
        }
        
        bool unresolved = true;
        while (unresolved) {

            set<int> can_numb;
            for (auto b: ballots) can_numb.insert(b[0]); 

            map<int, int> can_votes;
            for (auto b: ballots) can_votes[b[0]] += 1;

            int low  = INT_MAX;
            int high = 0;
            for (auto& kv : can_votes) {
                if (kv.second < low) low   = kv.second;
                if (kv.second > high) high = kv.second;
            }

            if (low == high) {                    // tie 
                for (int x : can_numb) cout << candidates[x] << endl;
                unresolved = false;
            } 
            else if (high > ballots.size() / 2) { // majority
                for (auto& kv : can_votes) {
                    if (kv.second == high)
                        cout << candidates[kv.first] << endl;
                }
                unresolved = false;
            } 
            else {                                // erase losers and loop again
                for (auto& b: ballots) 
                    for (auto& kv : can_votes) 
                        if (kv.second == low)
                            b.erase(remove(b.begin(), b.end(), kv.first), b.end());
            }
        }
        if (i != cases - 1) cout << endl;
    }
    return 0;
}
