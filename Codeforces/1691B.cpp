#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#define ll long long
#include <map>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        map<int,vector<int>> copies;
        int arr[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            copies[arr[i]].push_back(i);
        }
        bool fine = true;
        for (auto& p: copies) {
            if (p.second.size() == 1) {
                fine = false;
            }
        }
        if (!fine) {
            cout << "-1\n";
            continue;
        }
        int ans[n];
        for (auto& p: copies) {
            vector<int> v = p.second;
            for (int i = 0; i < v.size(); i++) {
                ans[v[(i + 1) % (int)v.size()]] = v[i];
            }
        }
        for (int i: ans) {
            cout << i + 1 << ' ';
        }
        cout << '\n';
    }
}
