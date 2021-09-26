#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

void solve () {
    int n;
    long long s;
    cin >> n >> s;
    vector<long long> weight(n), cost(n);
    for(int i = 0; i < n; i++) {
        cin >> weight[i];
    }
    vector<long long> pref = {0};
    for(int i = 0; i < n; i++) {
        cin >> cost[i];
        pref.push_back(pref.back() + cost[i]);
    }
    int strt = -1;
    for(int i = 0; i < n; i++) {
        if(weight[i] <= s) {
            strt = i;
            break;
        }
    }
    if(strt == -1) {
        cout << 0;
        return;
    }
    int l = strt;
    int r = strt;
    int curWeight = weight[strt];
    long long myMax = cost[strt];
    while(r != n - 1) {
        if(weight[r + 1] + curWeight <= s) {
            r++;
            curWeight += weight[r];
        } else {
            myMax = max(myMax, pref[r + 1] - pref[l]);
            curWeight -= weight[l];
            l++;
        }
    }
    if(curWeight <= s) {
        myMax = max(myMax, pref[n] - pref[l]);
    }
    cout << myMax;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
