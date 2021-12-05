#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#define ll long long
using namespace std;

vector<int> removeDuplicates(vector<int> v) {
    set<int> s;
    for (int i: v) {
        s.insert(i);
    }
    v.clear();
    for (int i: s) {
        v.push_back(i);
    }
    return v;
}

int main() {
    //freopen("msched.out", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> a(n); //[val,ind]
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    a = removeDuplicates(a);
    n = a.size();
    int myMax = 0;
    for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] < myMax) {
            continue;
        }
        for (int k = a[i]; k <= (int) 1e6; k += a[i]) {
            int l = i;
            int r = n - 1;
            while (l != r) {
                int m = (l + r + 1)/2;
                if (a[m] <= a[i] + k - 1) {
                    l = m;
                } else {
                    r = m - 1;
                }
            }
            myMax = max(myMax, a[l] - k);
        }
    }
    cout << myMax;

}
