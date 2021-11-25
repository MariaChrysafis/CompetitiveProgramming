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
vector<int> perform (vector<int> v) {
    int l = 0;
    int r = v.size() - 1;
    deque<int> ans;
    while (l <= r) {
        if (v[l] < v[r]) {
            ans.push_front(v[l]);
            l++;
        } else {
            ans.push_back(v[r]);
            r--;
        }
    }
    vector<int> ansr;
    for (int i: ans) {
        ansr.push_back(i);
    }
    return ansr;
}
vector<int> perform1 (vector<int> v) {
    int l = 0;
    int r = v.size() - 1;
    deque<int> ans;
    while (l <= r) {
        if (v[r] < v[l]) {
            ans.push_back(v[r]);
            r--;
        } else {
            ans.push_front(v[l]);
            l++;
        }
    }
    vector<int> ansr;
    for (int i: ans) {
        ansr.push_back(i);
    }
    return ansr;
}
vector<int> rev_perform (vector<int> v) {
    int l = 0;
    int r = v.size() - 1;
    deque<int> ans;
    while (l <= r) {
        if (v[l] < v[r]) {
            ans.push_back(v[r]);
            r--;
        } else {
            ans.push_front(v[l]);
            l++;
        }
    }
    vector<int> ansr;
    for (int i: ans) {
        ansr.push_back(i);
    }
    return ansr;
}

vector<int> rev_perform1 (vector<int> v) {
    int l = 0;
    int r = v.size() - 1;
    deque<int> ans;
    while (l <= r) {
        if (v[r] < v[l]) {
            ans.push_front(v[l]);
            l++;
        } else {
            ans.push_back(v[r]);
            r--;
        }
    }
    vector<int> ansr;
    for (int i: ans) {
        ansr.push_back(i);
    }
    return ansr;
}

vector<int> solve () {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<int> ans = rev_perform1(v);
    if (perform1(rev_perform1(v)) == v) {
        return rev_perform1(v);
    }
    if (perform(rev_perform1(v)) == v) {
        return rev_perform1(v);
    }
    if (perform(rev_perform(v)) == v) {
        return rev_perform(v);
    }
    if (perform1(rev_perform(v)) == v) {
        return rev_perform(v);
    }
    return {-1};
}
void print (vector<int> v) {
    for (int i: v) {
        cout << i << ' ';
    }
    cout << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        vector<int> v = solve();
        for (int i: v) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}
