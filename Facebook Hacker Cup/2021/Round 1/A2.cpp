#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;
long long solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    long long ans = 0;
    for(int i = 0; i < n - 1; i++){
        if(s[i] != s[i + 1] && s[i] != 'F' && s[i + 1] != 'F'){
            ans += ((i + 1) * (n - i - 1)) % MOD;
            ans %= MOD;
        }
        ans %= MOD;
    }
    char lastNotF = '?';
    int ind = -1;
    if(s[0] != 'F') lastNotF = s[0], ind = 0;
    if(s[1] != 'F') lastNotF = s[1], ind = 1;

    for(int i = 2; i < n; i++){
        if(lastNotF == 'O' && s[i] == 'X' && s[i - 1] == 'F'){
            //cout << ind + 1 << " " << s.length() - i << endl;
            ans += (ind + 1) * (s.length() - i);
        }
        if(lastNotF == 'X' && s[i] == 'O' && s[i - 1] == 'F'){
            //1
            //6
            //XFFFFOcout << ind + 1 << " " << s.length() - i << endl;
            ans += (ind + 1) * (s.length() - i);
        }
        if(s[i] != 'F'){
            lastNotF = s[i];
            ind = i;
        }
        ans %= MOD;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": " << solve();
        if(i != t) cout << '\n';
    }

}
