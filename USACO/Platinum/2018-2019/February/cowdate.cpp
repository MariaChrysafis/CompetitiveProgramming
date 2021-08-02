#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <set>
#include <iomanip>
using namespace std;
void solve(){
    int n;
    cin >> n;
    vector<long double> p(n);
    for(int i = 0; i < n; i++){
        cin >> p[i];
        p[i] /= (long double)1000000.0;
    }
    int l = 0;
    int r = 0;
    long double pref = 1;
    long double pref_sm = 0;
    long double myMax = 0;
    long double identity = 1.0;
    while(l < n && r < n){
        pref *= (identity - p[r]);
        pref_sm += p[r]/(identity - p[r]);
        myMax = max(pref * pref_sm, myMax);
        if(pref_sm >= identity){
            pref_sm -= p[l]/(identity - p[l]);
            pref /= (identity - p[l]);
            pref /= (identity - p[r]);
            pref_sm -= p[r]/(identity - p[r]);
            l++;
        }else{
            r++;
        }
    }
    cout << floor(myMax * 1e6) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("cowdate.in", "r", stdin);
    freopen("cowdate.out", "w", stdout);
    solve();
}
