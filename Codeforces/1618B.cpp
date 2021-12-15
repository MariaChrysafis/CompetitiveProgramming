#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#define pb push_back
#define mp make_pair

#define ll long long
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        n -= 2;
        vector<string> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        string str = v[0];
        for (int i = 1; i < n; i++) {
            if (v[i][0] != v[i - 1][1]) {
                str += v[i][0];
            }
            str += v[i][1];
        }
        if (str.length() != n + 2) {
            str += 'a';
        }
        cout << str << '\n';
    }
}
