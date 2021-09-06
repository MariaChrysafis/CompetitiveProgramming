#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
 
using namespace std;
const int MAX = 3e5 + 100;
vector<long long> pref;
void solve(){
    long long a;
    cin >> a;
    vector<int> dig;
    long long dum = a;
    while(dum != 0){
        dig.push_back(dum % 10);
        dum -= dum % 10;
        dum /= 10;
    }
    //reverse(dig.begin(), dig.end());
    vector<long long> prod[2];
    for(int i = 0; i < dig.size(); i++){
        prod[i % 2].push_back(dig[i]);
    }
    long long res = 1;
    for(int i = 0; i < 2; i++){
        long long ans = 0;
        for(int j = 0; j < prod[i].size(); j++){
            ans += pow(10, j) * prod[i][j];
        }
        res *= (ans + 1);
        //cout << ans << " ";
    }
    //cout << endl;
    cout << res - 2 << '\n';
}
 
int main() {
    pref.push_back(0);
    while(pref.size() != MAX){
        pref.push_back(pref.back() ^ pref.size());
        //cout << pref.back() << endl;
    }
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
