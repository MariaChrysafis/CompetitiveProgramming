#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <set>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    string s;
    cin >> s;
    set<int> mySet;
    for (int i = 0; i < s.length(); i++) if (s[i] == '1') mySet.insert(i);
    while (Q--) {
        int c, k;
        cin >> c >> k;
        if (c == 0) mySet.insert(k);
        else if (c == 1) mySet.erase(k);
        else if (c == 2) cout << (bool)mySet.count(k) << '\n';
        else if (c == 3) {
            if (mySet.lower_bound(k) == mySet.end()) cout << "-1\n";
            else cout << *mySet.lower_bound(k) << '\n';
        } else if (c == 4) {
            if (mySet.upper_bound(k) == mySet.begin()) cout << "-1\n";
            else cout << *(--mySet.upper_bound(k)) << '\n';
        }
    }
}
