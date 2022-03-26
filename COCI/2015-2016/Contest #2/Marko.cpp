#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<string> vec(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i];
    }
    string s;
    cin >> s;
    set<int> id[10];
    id[2] = {'a', 'b', 'c'};
    id[3] = {'d', 'e', 'f'};
    id[4] = {'g', 'h', 'i'};
    id[5] = {'j', 'k', 'l'};
    id[6] = {'m', 'n', 'o'};
    id[7] = {'p', 'q', 'r', 's'};
    id[8] = {'t', 'u', 'v'};
    id[9] = {'w', 'x', 'y', 'z'};
    int c = 0;
    for (int i = 0; i < N; i++) {
        if (vec[i].size() != s.size()) {
            continue;
        }
        bool f = true;
        for (int j = 0; j < vec[i].size(); j++) {
            if (!id[(int)(s[j] - '0')].count(vec[i][j])) {
                f = false;
            }
        }
        c += f;
    }
    cout << c;
}
