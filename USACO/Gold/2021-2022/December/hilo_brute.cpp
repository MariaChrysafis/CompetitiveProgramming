#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int p[n];
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    for (int i = 0; i <= n; i++) {
        string s;
        int l = 0;
        int r = n;
        for (int j = 0; j < n; j++) {
            if (p[j] > i && r >= p[j]) {
                s += 'H';
                r = p[j] - 1;
            } else if (p[j] <= i && l < p[j]){
                s += 'L';
                l = p[j];
            } else {
                //if (p[j] > i) s += 'H';
                //else s += 'L';
                //s += '#';
            }
            if (r == l) {
                break;
                //s += '?';
            }
        }
        int cntr = 0;
        for (int j = 0; j < s.length(); j++) {
            if (s[j] == 'H' && s[j + 1] == 'L') {
                cntr++;
            }
        }
        //cout << s.length() << '\n';
        cout << cntr << '\n';
    }
}
