#include <iostream>
#include <vector>
#include <map>
using namespace std;

void solve(string s, int k) {
    map<char,int> m;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        while (c != 'a') {
            if (!m[c]) {
                if (k == 0) {
                    break;
                }
                m[c] = true;
                k--;
            }
            c--;
        }
        s[i] = c;
    }
    cout << s << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        solve(s, k);
    }
}
