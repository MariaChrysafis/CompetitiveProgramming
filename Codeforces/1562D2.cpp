#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
bool isPrime(int x){
    for(int i = 2; i <= sqrt(x) + 2; i++){
        if(x % i == 0){
            return false;
        }
    }
    return true;
}
vector<int> pref;
int pluses(int l, int r){
    if(l > r) return 0;
    return pref[r + 1] - pref[l];
}
int minuses(int l, int r){
    if(l > r) return 0;
    return (r - l + 1) - pluses(l , r);
}
int signedSum(int l, int r, int x){
    int delta1 = pluses(l, x - 1) - minuses(l, x - 1);
    int delta2 = pluses(x + 1, r) - minuses(x + 1, r);
    return delta1 - delta2;
}
int binSearch(int left, int right, int l, int r){
    if(l > r){
        cout << "YESEYEST\n";
        return 3;
    }
    //cout << endl;
    //cout << endl;
    int m = (l + r)/2;
    int xl = signedSum(left, right, l);
    int xm = signedSum(left, right, m);
    int xr = signedSum(left, right, r);
    //cout << xr << " " << xm << " " << xl << " " << l << " " << r << endl;
    if(xl == 0) { return l; }
    if(xm == 0) { return m; }
    if(xr == 0) { return r; }
    if((xm > 0 && xr < 0) || (xm < 0 && xr > 0)) {
        return binSearch(left, right, m + 1, r- 1);
    }else if((xm > 0 && xl < 0) || (xm < 0 && xl > 0)){
        return binSearch(left, right, l + 1, m - 1);
    }else{
        cout << "NO\n" << " " << left << " " << right << endl;
    }
}
int find_val(int l, int r){
    for(int i = l; i <= r; i++){
        if(signedSum(l, r, i) == 0){
            return i;
        }
    }
    return -1;
}
void solve(){
    int n;
    cin >> n;
    int q;
    cin >> q;
    string s;
    cin >> s;
    for(int i = 0; i < s.length(); i++){
        if(i % 2 == 1){
            if(s[i] == '+') s[i] = '-';
            else s[i] = '+';
        }
    }
    pref.resize(s.length() + 1);
    pref[0] = 0;
    for(int i = 1; i <= s.length(); i++){
        pref[i] = pref[i - 1] + (s[i - 1] == '+');
    }
    //cout << s << endl;
    while(q--){
        int l, r;
        cin >> l >> r;
        l--, r--;
        int plus = pluses(l, r);
        int minus = minuses(l, r);
        if(plus == minus){
            cout << "0\n";
            continue;
        }
        if((r - l + 1) % 2 == 1){
            cout << "1\n";
            cout << binSearch(l, r, l, r) + 1 << endl;
            continue;
        }
        cout << "2\n";
        cout << r + 1 << " " << binSearch(l, r - 1, l, r - 1) + 1 << '\n';
    }
 
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
