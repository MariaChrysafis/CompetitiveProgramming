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

bool solve () {
    string s;
    cin >> s;
    int a, b, c;
    a = b = c = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'A') {
            a++;
        } else if (s[i] == 'B') {
            b++;
        } else {
            c++;
        }
    }
    //cout << a << " " <<  c << " " << b << " ";
    return (a + c == b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        bool b = solve();
        if(b) cout << "YES\n";
        else cout << "NO\n";
    }

}
