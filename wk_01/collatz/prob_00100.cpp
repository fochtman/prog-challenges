#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int in_i;
    int in_j;
    while (cin >> in_i >> in_j) {
        int i = in_i <= in_j ? in_i : in_j;
        int j = in_i <= in_j ? in_j : in_i;
        vector<int> rng(j - i + 1, 0);
        iota(rng.begin(), rng.end(), i);
        int cyc_len = 1;
        for (int n : rng) {
           int counter = 1;
           while (n != 1) {
               n = n % 2 == 0 ? n /= 2 : 3 * n + 1;
               counter++;
           }
           cyc_len = counter > cyc_len ? counter : cyc_len;
        }
        cout << in_i << " " << in_j << " " << cyc_len << endl;
    }
    return 0;
}

