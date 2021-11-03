#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <set>
#define ll long long
using namespace std;
struct interval_by_length {
    ll l, r;
    bool operator<(const interval_by_length& i1) const {
        if (i1.r - i1.l == r - l) {
            return (i1.l < l);
        }
        return (i1.r - i1.l < r - l);
    }
};
struct interval_by_left {
    ll l, r;
    bool operator<(const interval_by_left& i1) const {
        if (i1.l == l) {
            return (i1.r > r);
        }
        return (i1.l > l);
    }
};
int solver (vector<int> arr) {
    vector<vector<int>> partition;
    partition.emplace_back();
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 0) {
            partition.emplace_back();
            continue;
        }
        partition.back().push_back(arr[i]);
    }
    if (partition.size() >= 2) {
        int ansr = 0;
        for (vector<int> vec: partition) {
            ansr = max(ansr, solver(vec));
        }
        return ansr;
    }
    int n = arr.size();
    map<int,vector<int>> oc;
    set<int> s;
    for (int i = 0; i < n; i++) {
        s.insert(arr[i]);
        oc[arr[i]].push_back(i);
    }
    set<interval_by_length> mySet1;
    set<interval_by_left> mySet2;
    mySet1.insert({0, n - 1});
    mySet2.insert({0, n - 1});
    ll myMax = n;
    for (auto p: oc) {
        for (int i: p.second) {
            auto it = mySet2.lower_bound({i + 1, -1});
            it--;
            assert(it != mySet2.end());
            const interval_by_left intrval = *it;
            mySet2.erase(it);
            mySet1.erase({intrval.l, intrval.r});
            if (i - 1 >= intrval.l) {
                mySet1.insert({intrval.l, i - 1});
                mySet2.insert({intrval.l, i - 1});
            }
            if (i + 1 <= intrval.r) {
                mySet1.insert({i + 1, intrval.r});
                mySet2.insert({i + 1, intrval.r});
            }
        }
        if (mySet1.empty()) {
            break;
        }
        auto it = mySet1.begin();
        auto itr = s.upper_bound(p.first);
        ll x = *itr;
        interval_by_length i1 = *it;
        myMax = max(myMax,(i1.r - i1.l + 1) * x);
    }
    return myMax;
}
void print(vector<int> v) {
    for (int i: v) {
        cout << i << ' ';
    }
    cout << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<string> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i].resize(m);
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }
    vector<int> height(n);
    for (int i = 0; i < n; i++) {
        height[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == '*') {
                break;
            }
            height[i]++;
        }
    }
    int myMax = 0;
    for (int i = 0; i < m; i++) {
        myMax = max(myMax, solver(height));
        //print(height);
        for (int j = 0; j < n; j++) {
            height[j]--;
            if (height[j] == -1) {
                height[j] = 0;
                for (int k = i + 1; k < m; k++) {
                    if (arr[j][k] == '*') {
                        break;
                    }
                    height[j]++;
                }
            }
        }
        //print(height);
        myMax = max(myMax, solver(height));
    }
    cout << myMax;
}
