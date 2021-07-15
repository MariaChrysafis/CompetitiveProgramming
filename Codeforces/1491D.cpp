#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
vector<int> a, b;
const int MOD = 998244353;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
int solve(){
    long long u, v;
    cin >> u >> v;
    if(u > v){
        return false;
    }
    if(u == v){
        return true;
    }
    if((u & (v - u)) == v - u){
        return true;
    }
    int cntr1 = 0;
    int cntr2 = 0;
    for(int i = 0; i < 30; i++){
        if(u & (1 << i)){
            cntr1++;
        }
        if(v & (1 << i)){
            cntr2++;
        }
        if(cntr1 < cntr2){
            return false;
        }
    }
    return true;
}
int main() {
    int t;
    cin >> t;
    while(t--){
        int b = solve();
        string s;
        if(b == 1) s = "YES";
        else if(b == 0) s = "NO";
        else s = "Maybe";
        cout << s << endl;
    }
}
