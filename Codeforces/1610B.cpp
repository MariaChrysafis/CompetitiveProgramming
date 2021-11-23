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
#define ll int64_t
using namespace std;
bool kalindrome (vector<int> v, int k) {
    vector<int> vec;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] != k) {
            vec.push_back(v[i]);
        }
    }
    vector<int> orig = vec;
    reverse(vec.begin(), vec.end());
    return (vec == orig);
}
bool solve() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    if (kalindrome(arr, -1)) {
        return true;
    }
    if (kalindrome(arr, arr[0])) {
        return true;
    }
    if (kalindrome(arr, arr[1])) {
        return true;
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] != arr[n - 1 - i]) {
            if (kalindrome(arr, arr[i])) {
                return true;
            }
            if (kalindrome(arr, arr[n - 1 - i])) {
                return true;
            }
            return false;
        }
    }
    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        bool b = solve();
        if (b) cout << "YES\n";
        else cout << "NO\n";
    }
}
