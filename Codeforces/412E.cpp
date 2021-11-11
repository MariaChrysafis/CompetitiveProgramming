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
string s;
ll right (int x) {
    int firstPeriod = -1;
    for (int j = x + 1; j < s.length(); j++) {
        if (s[j] == '.') {
            firstPeriod = j;
            break;
        }
        if (s[j] == '_' || s[j] == '@') {
            return 0;
        }
    }
    if (firstPeriod == -1 || firstPeriod == x + 1) {
        return 0;
    }
    int cntr = 0;
    for (int j = firstPeriod + 1; j < s.length(); j++) {
        if (s[j] >= 'a' && s[j] <= 'z') {
            cntr++;
        } else {
            break;
        }
    }
    return cntr;
}
ll left (int x) {
    int cntr = 0;
    for (int i = x - 1; i >= 0; i--) {
        if (s[i] == '.' || s[i] == '@') {
            break;
        }
        cntr += (s[i] >= 'a' && s[i] <= 'z');
    }
    return cntr;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> s;
    ll ans = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '@') {
            ans += left(i) * right(i);
        }
    }
    cout << ans;
}
