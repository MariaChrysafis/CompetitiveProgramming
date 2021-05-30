#include <iostream>
#include <vector>
#include <set>
using namespace std;
vector<bool> v;
vector<bool> hv;
long long n;
bool valid(long long x){
    if(x == 0){ v[0] = 1; return true;}
    if(x < 0) return false;
    if(hv[x]) return v[x];
    v[x] = valid(x - 11) || valid(x - 111);
    hv[x] = true;
    return v[x];
}
 
int main(){
    n = 111 * 11 * 11 * 11;
    v.resize(n), hv.resize(n);
    for(int i = 0; i < n; i++) v[i] = false, hv[i] = false;
    set<long long> s;
    for(int i = 0; i < n; i++) {
        if(valid(i)){
            s.insert(i);
        }
    }
    long long t;
    cin >> t;
    while(t--){
        long long x;
        cin >> x;
        if(x > n){
            cout << "YES" << endl;
            continue;
        }else{
            if(s.count(x)) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
}
