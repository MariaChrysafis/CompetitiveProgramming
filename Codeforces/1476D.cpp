#include <iostream>
#include <vector>
 
using namespace std;
 
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    //let's compute the things for the left
    vector<int> pref(n + 1);
    pref[0] = 0;
    pref[1] = (s[0] == 'L');
    for (int i = 2; i <= n; i++){
        char c = (s[i - 1]);
        if (c == 'R'){
            pref[i] = 0;
            continue;
        }
        if (c == 'L' && s[i - 2] == 'L'){
            pref[i] = 1;
            continue;
        }
        pref[i] = pref[i - 2] + 2;
    }
    vector<int> suf(n + 1);
    suf[(int)suf.size() - 1] = 0;
    suf[(int)suf.size() - 2] = (s[n - 1] == 'R');
    for(int i = (int)suf.size() - 3; i >= 0; i--){
        char c = s[i];
        if(c == 'L'){
            suf[i] = 0;
            continue;
        }
        if (c == 'R' && s[i + 1] == 'R'){
            suf[i] = 1;
            continue;
        }
        suf[i] = suf[i + 2] + 2;
    }
    for(int i = 0; i <= n; i++){
        cout << suf[i] + pref[i] + 1 << " ";
    }
    cout << '\n';
}
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
