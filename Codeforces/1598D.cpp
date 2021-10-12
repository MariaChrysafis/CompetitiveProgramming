#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <algorithm>

#define ll long long

using namespace std;
void solve () {
    long long n;
    cin >> n;
    vector<pair<long long,long long>> vec(n);
    map<long long,long long> myMap1, myMap2;
    map<long long, set<long long>> myMap;
    for (int i = 0; i < n; i++) {
        cin >> vec[i].first >> vec[i].second;
        myMap1[vec[i].first]++, myMap2[vec[i].second]++;
        myMap[vec[i].first].insert(vec[i].second);
    }
    long long ff = 0;
    for (auto p: myMap1) {
        long long key = p.first;
        for (long long i: myMap[key]) {
            ff += (myMap1[key] - 1) * (myMap2[i] - 1);
        }
    }
    cout << n * (n - 1) * (n - 2)/6 - ff << endl;

}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
