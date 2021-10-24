#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
int remove (string s, char c) {
    string str = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != c) {
            str += s[i];
        }
    }
    string new_str = str;
    reverse(new_str.begin(), new_str.end());
    if (new_str != str) {
        return (int)1e9;
    }
    vector<int> vec;
    int a = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == c) {
            a++;
        } else {
            vec.push_back(a);
            a = 0;
        }
    }
    vec.push_back(a);
/*
    for (int i: vec) {
        cout << i << ' ';
    }
    cout << endl;
*/
    int tot = 0;
    for (int i: vec) {
        tot += i;
    }
    int ans = 0;
    for (int i = 0; i < vec.size()/2; i++) {
        ans += 2 * min(vec[i], vec[vec.size() - 1 - i]);
    }
    if (vec.size() % 2 == 1) {
        ans += vec[vec.size()/2];
    }
    return tot - ans;
}
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int myMin = (int)1e9;
    //cout << remove(s, 'y') << endl;
    //return;
    for (char c = 'a'; c <= 'z'; c++) {
        myMin = min(myMin, remove(s, c));
    }
    if (myMin == (int)1e9) {
        cout << "-1\n";
        return;
    }
    cout << myMin << '\n';
    return;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
