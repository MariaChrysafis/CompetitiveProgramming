#include <iostream>
#define all(s) s.begin(),s.end()
using namespace std;
int val(char c){
    if(c == '+') return 1;
    return -1;
}
void solve(){
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    int pref[s.length()];
    int suf[s.length()];
    pref[0] = val(s[0]);
    for(int i = 1; i < s.length(); i++){
        pref[i] = pref[i - 1] + val(s[i]);
    }
    int prefMax[s.length()];
    int prefMin[s.length()];
    int sufMax[s.length()];
    int sufMin[s.length()];
    prefMax[0] = max(pref[0], 0);
    prefMin[0] = min(pref[0], 0);
    for(int i = 1; i < s.length(); i++){
        prefMax[i] = max(prefMax[i - 1], pref[i]);
        prefMin[i] = min(prefMin[i - 1], pref[i]);
    }
    suf[s.length() - 1] = val(s[s.length() - 1]);
    for(int i = s.length() - 2; i >= 0; i--){
        suf[i] = suf[i + 1] + val(s[i]);
    }
    sufMax[s.length() - 1] = max(suf[s.length() - 1], 0);
    sufMin[s.length() - 1] = min(suf[s.length() - 1], 0);
    for(int i = s.length() - 2; i >= 0; i--){
        sufMax[i] = max(sufMax[i + 1] + val(s[i]), val(s[i]));
        sufMin[i] = min(sufMin[i + 1] + val(s[i]), val(s[i]));
        sufMax[i] = max(sufMax[i], 0);
        sufMin[i] = min(sufMin[i], 0);
    }
    //cout << prefMin[0] << endl;
    while(q--){
        int l, r;
        cin >> l >> r;
        l--, r--;
        int myMax1;
        if(l != 0) myMax1 = prefMax[l - 1];
        else myMax1 = 0;
        int myMax2;
        if(l != 0) myMax2 = pref[l - 1];
        else myMax2 = 0;
        if(r + 1 != n) myMax2 += sufMax[r + 1];
        int myMin1;
        if(l != 0) myMin1 = prefMin[l - 1];
        else myMin1 = 0;
        int myMin2;
        if(l != 0) myMin2 = pref[l - 1];
        else myMin2 = 0;
        if(r + 1 != n) myMin2 += sufMin[r + 1];
        cout << max(myMax1,myMax2) - min(myMin1, myMin2) + 1 << endl;
    }
}
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
