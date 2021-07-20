#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
void solve() {
    long long a, b, q;
    cin >> a >> b >> q;
    vector<long long> pref(3 * a * b);
    pref[0] = 0;
    for(int i = 1; i < pref.size(); i++){
        pref[i] = pref[i - 1] + ((i % a) % b != (i % b) % a);
    }
    while(q--){
        long long l, r;
        cin >> l >> r;
        long long len = (r - l)/(a * b);
        l %= (a * b), r %= (a * b);
        l += (a * b), r += (a * b);
        if(r < l) r += (a * b);
        cout << pref[r] - pref[l - 1] + len * pref[a * b] << ' ';
    }
    cout << '\n';
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
