#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <set>
#include <iomanip>
#define ll unsigned long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int x;
    cin >> x;
    vector<ll> arr(n);
    set<int> s;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        s.insert(arr[i]);
    }
    map<ll, vector<pair<int,int>>> myMap;
    for (int i = 0; i < n; i++) {
        if (x - arr[i] < 0) {
            continue;
        }
        for (pair<int,int> p: myMap[x - arr[i]]) {
            if (p.first == i || p.second == i) {
                continue;
            }
            cout << p.first + 1 << " " << p.second + 1 << " " << i + 1 << '\n';
            return 0;
        }
        for (int j = i + 1; j < n; j++) {
            if (s.count(x - (arr[i] + arr[j]))) {
                myMap[arr[i] + arr[j]].emplace_back(i, j);
            }
        }
    }
    cout << "IMPOSSIBLE";
}
