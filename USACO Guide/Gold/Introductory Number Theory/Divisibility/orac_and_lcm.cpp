#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <climits>
#include <vector>
#include <set>

#define ll long long

using namespace std;
vector<pair<int,int>> fact(int n) {
    vector<pair<int,int>> vec;
    const int SQ = sqrt(n);
    for (int i = 2; i <= SQ; i++) {
        int cntr = 0;
        while (n % i == 0) {
            n /= i;
            cntr++;
        }
        if (cntr) {
            vec.push_back(make_pair(i, cntr));
        }
    }
    if (n != 1) {
        vec.push_back(make_pair(n, 1));
    }
    return vec;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    map<int,vector<int>> myMap;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        for (auto p: fact(x)) {
            myMap[p.first].push_back(p.second);
        }
    }
    long long ans = 1;
    for (auto p: myMap) {
        sort(myMap[p.first].begin(), myMap[p.first].end());
        if (myMap[p.first].size() == n) {
            ans *= pow(p.first, max(myMap[p.first][0], myMap[p.first][1]));
        } else if (myMap[p.first].size() == n - 1){
            ans *= pow(p.first, myMap[p.first][0]);
        }
    }
    cout << ans << endl;
}
