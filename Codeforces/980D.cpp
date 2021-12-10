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
#define ll long long
using namespace std;
vector<int> v;
int count (int s) {
    //how many things have <= s distinct values
    int n = v.size();
    int l = 0;
    int r = 0;
    int myMap[n + 1]; int farthest[n + 1];
    for (int i = 0; i <= n; i++) {
        myMap[i] = 0;
        farthest[i] = 0;
    }
    int sum = (v[0] != 0); //how many distinct values
    myMap[v[0]]++;
    //cout << sum << endl;
    while (l <= r + 1 && l < n) {
        farthest[l] = max(farthest[l], r);
        if (l == n) break;
        //cout << l << " " << r << " " << sum << '\n';
        if (r + 1 != n && (myMap[v[r + 1]] == 0 && v[r + 1] != 0) + sum <= s) {
            sum += (myMap[v[r + 1]] == 0 && v[r + 1] != 0);
            myMap[v[r + 1]]++;
            r++;
        } else {
            sum -= (myMap[v[l]] == 1 && v[l] != 0);
            myMap[v[l]]--;
            l++;
        }
        //cout << l << " " << r << endl;
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += farthest[i] - i + 1;
        //2
        //5 5cout << i << " " << farthest[i] << '\n';
    }
    //cout << ans << endl;
    return ans;

}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        if (v[i] == 0) continue;
        for (int j = 2; j <= 10000; j++) {
            while (abs(v[i]) % (j * j) == 0) {
                v[i] /= j * j;
            }
        }

    }
    set<ll> s;
    for (int i = 0; i < v.size(); i++) {
        s.insert(v[i]);
    }
    map<ll,ll> myMap;
    int cntr = 0;
    for (ll i: s) {
        myMap[i] = ++cntr;
    }
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == 0) myMap[v[i]] = 0;
        else v[i] = myMap[v[i]];
    }
    vector<int> dp(n + 2);
    for (int i = 0; i <= n + 1; i++) {
        dp[i] = count(i);
    }
    cout << count(1) << ' ';
    for (int i = 2; i <= n; i++) {
        cout << -dp[i - 1] + dp[i] << ' ';
    }
}
