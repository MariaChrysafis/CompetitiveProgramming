#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;
vector<pair<int,int>> vec;
double myMap[(int)2e5 + 1];
pair<double,vector<int>> find_max (int X) {
    //we have X messages total that are pinned
    for (int i = 0; i <= (int)2e5; i++) {
        myMap[i] = 0;
    }
    vector<pair<int,int>> v;
    for (auto &p: vec) {
        v.push_back(p);
        if (v.back().second >= X) {
            myMap[v.back().first] += 1;
        } else {
            myMap[v.back().first] += (double)v.back().second/(double)X;
        }
    }
    vector<pair<double,int>> ans;
    vector<int> res_vec;
    for (int i = 0; i <= (int)2e5; i++) {
        if (myMap[i] == 0) {
            continue;
        }
        auto p = make_pair(i, myMap[i]);
        ans.push_back({p.second, p.first});
    }
    sort(ans.begin(), ans.end());
    reverse(ans.begin(), ans.end());
    double res = 0;
    for (int i = 0; i < min(X, (int)ans.size()); i++) {
        res += ans[i].first;
        res_vec.push_back(ans[i].second);
    }
    return {res, res_vec};
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vec.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i].first >> vec[i].second;
    }
    double best = 0;
    vector<int> ans;
    for (int i = 0; i <= 20; i++) {
        if (find_max(i).first > best) {
            ans = find_max(i).second;
            best = find_max(i).first;
        }
    }
    cout << ans.size() << '\n';
    for (int i: ans) {
        cout << i << ' ';
    }
}
