#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

string sorted(string s) {
    sort(s.begin(), s.end());
    return s;
}

void print (vector<pair<int,int>> vec) {
    cout << vec.size() << '\n';
    for (pair<int,int> p: vec) {
        cout << p.first + 1 << " " << p.second + 1 << '\n';
    }
    cout << '\n';
}

void solve () {
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;
    n = s1.length();
    map<int,int> oc1, oc2;
    for(char c: s1) oc1[c]++;
    for(char c: s2) oc2[c]++;
    vector<pair<int,int>> vec;
    for (int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if (s1[i] == s1[j]) {
                vec.emplace_back(j, i);
                swap(s1[j], s2[i]);
                break;
            }
            if (s1[i] == s2[j]) {
                vec.emplace_back(j, j);
                swap(s1[j], s2[j]);
                vec.emplace_back(j, i);
                swap(s1[j], s2[i]);
                break;
            }
        }
    }
    if(s1 == s2) {
        cout << "Yes\n";
        assert(vec.size() <= 2 * n);
        print(vec);
        return;
    }
    cout << "No\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

}
