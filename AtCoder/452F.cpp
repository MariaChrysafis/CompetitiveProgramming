#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#include <stack>

using namespace std;
void put () {
    cout << "YES\n";
    exit(0);
}

void check (vector<int>&p, vector<int>&myMap, int a, int b) {
    if (a == b) return;
    if (a % 2 == b % 2 && a != b) {
        if ((a + b)/2 <= p.size() && myMap[(a + b)/2] >= myMap[a] && myMap[(a + b)/2] <= myMap[b]) {
            //cout << a << " "<< b << '\n';
            put();
        }
        swap(a, b);
        if ((a + b)/2 <= p.size() && myMap[(a + b)/2] >= myMap[a] && myMap[(a + b)/2] <= myMap[b]) {
            put();
        }
    }
    if (2 * a - b >= 1 && 2 * a - b <= p.size()) {
        if (myMap[a] >= myMap[b] && myMap[a] <= myMap[2 * a - b]) {
            put();
        }
        if (myMap[a] <= myMap[b] && myMap[a] >= myMap[2 * a - b]) {
            put();
        }
    }
    swap(a, b);
    if (2 * a - b >= 1 && 2 * a - b <= p.size()) {
        if (myMap[a] >= myMap[b] && myMap[a] <= myMap[2 * a - b]) {
            put();
        }
        if (myMap[a] <= myMap[b] && myMap[a] >= myMap[2 * a - b]) {
            put();
        }
    }
}
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> p(N), myMap(N + 1);
    for (int i = 0; i < N; i++) {
        cin >> p[i];
        myMap[p[i]] = i + 1;
    }
    for (int i = 0; i < N; i++) {
        for (int j = i; j < min(i + 30, N); j++) {
            check(p, myMap, p[i], p[j]);
        }
    }
    cout << "NO\n";
}
