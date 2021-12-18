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
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
typedef long long ll;

using namespace std;
vector<pair<int,int>> arr; //[value inputted, how many more queries we have processed]
map<int,set<pair<int,int>>> myMap;
map<pair<int,int>,int> dp;
int rec (int val, int ind) {
    if (dp[{val, ind}]) {
        return dp[{val, ind}];
    }
    auto it = myMap[val].upper_bound({ind, -1});
    if (it == myMap[val].end()) {
        return val;
    }
    return dp[{val,ind}] = rec((*it).second, (*it).first + 1);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            cin >> x;
            arr.push_back({x, i});
        } else {
            int x, y;
            cin >> x >> y;
            myMap[x].insert({i, y});
        }
    }
    for (auto& p: arr) {
        cout << rec(p.first, p.second) << ' ';
    }
}
