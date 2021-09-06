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
    long long a, b;
    cin >> a >> b;
    if(pref[a - 1] == b){
        cout << a << endl;
    }else{
        cout << a + ((pref[a - 1] ^ a) == b) + 1 << endl;
    }
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
