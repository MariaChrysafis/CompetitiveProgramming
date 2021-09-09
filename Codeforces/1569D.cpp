#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <set>
#include <map>
#include <algorithm>
 
#define ll long long
using namespace std;
vector<long long> fact;
 
set<ll> vectorToSet(vector<ll> v) {
    set<ll> s;
    for (ll i: v) s.insert(i);
    return s;
}
 
void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> horizontalStreets(n), verticalStreets(m);
    set<ll> h, v;
    set<ll> xCoords, yCoords;
    for (ll i = 0; i < n; i++) {
        cin >> horizontalStreets[i];
    }
    for (ll i = 0; i < m; i++) {
        cin >> verticalStreets[i];
    }
    h = vectorToSet(horizontalStreets);
    v = vectorToSet(verticalStreets);
    xCoords = h;
    yCoords = v;
    vector<pair<ll, ll>> people;
    for (ll i = 0; i < k; i++) {
        ll x, y;
        cin >> x >> y;
        if (h.count(x) && v.count(y)) {
            continue;
        }
        xCoords.insert(x);
        yCoords.insert(y);
        people.push_back({x, y});
    }
    map<ll, ll> newX, newY;
    ll cntr = 0;
    ll maxX;
    for (ll i: xCoords) {
        newX[i] = cntr;
        cntr++;
    }
    maxX = cntr;
    cntr = 0;
    ll maxY;
    for (ll i: yCoords) {
        newY[i] = cntr;
        cntr++;
    }
    maxY = cntr;
    h.clear();
    v.clear();
    map<ll, ll> getYFromX, getXFromY;
    for (ll i = 0; i < n; i++) {
        horizontalStreets[i] = newX[horizontalStreets[i]];
        h.insert(horizontalStreets[i]);
    }
    for (ll i = 0; i < m; i++) {
        verticalStreets[i] = newY[verticalStreets[i]];
        v.insert(verticalStreets[i]);
    }
    vector<vector<ll>> ocX(maxX + 1);
    vector<vector<ll>> ocY(maxY + 1);
    for (ll i = 0; i < people.size(); i++) {
        people[i] = make_pair(newX[people[i].first], newY[people[i].second]);
        ocX[people[i].first].push_back(i);
        ocY[people[i].second].push_back(i);
    }
    ll cur = 0;
    ll ans = 0;
    map<ll, ll> myMap;
    for (ll i = 0; i <= maxX; i++) {
        if (h.count(i)) {
            ans += cur * (cur - 1) / 2;
            for (pair<int, int> p: myMap) {
                ans -= p.second * (p.second - 1) / 2;
            }
            myMap.clear();
            cur = 0;
        } else {
            cur += ocX[i].size();
            for (int j: ocX[i]) {
                myMap[people[j].second]++;
            }
        }
    }
    myMap.clear();
    cur = 0;
    for (ll i = 0; i <= maxY; i++) {
        if (v.count(i)) {
            ans += cur * (cur - 1) / 2;
            for (pair<ll, ll> p: myMap) {
                ans -= p.second * (p.second - 1) / 2;
            }
            myMap.clear();
            cur = 0;
        } else {
            cur += ocY[i].size();
            for (ll j: ocY[i]) {
                myMap[people[j].first]++;
            }
        }
    }
    cout << ans << endl;
    return;
 
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
 
}
