#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<pair<int, int>> vec(n);
    for (int i = 0; i < n; i++) {
        vec[i].first = arr[i];
        vec[i].second = i;
    }
    sort(vec.begin(), vec.end());
    reverse(vec.begin(), vec.end());
    int lastOc[512];
    for (int i = 0; i < 512; i++) {
        lastOc[i] = -1;
    }
    for (auto p: vec) {
        for (int i = 0; i < 512; i++) {
            if (lastOc[i] > p.second) {
                lastOc[p.first ^ i] = max(lastOc[p.first ^ i], p.second);
                //cout << (p.first ^ i) << " " << p.second << " " << p.first << endl;
            }
            //if (st[i].query(p.second + 1, n)) {
                //st[p.first ^ i].upd(p.second, true);
            //}
        }
        lastOc[0] = max(lastOc[0], p.second);
        lastOc[p.first] = max(lastOc[p.first], p.second);
        //st[0].upd(p.second, true);
        //st[p.first].upd(p.second, true);
    }
    //cout << lastOc[1] << endl;
    vector<int> ans;
    for (int i = 0; i < 512; i++) {
        if (lastOc[i] != -1) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << endl;
    for (int i: ans) {
        cout << i << " ";
    }
    cout << endl;
}
