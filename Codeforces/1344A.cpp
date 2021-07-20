#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
bool solve() {
    long long n;
    cin >> n;
    vector<long long> v(n);
    for(long long i = 0; i < n; i++) cin >> v[i];
    set<long long> s;
    for(long long i = 0; i < n; i++) s.insert((v[i] + i + n * 1000000000ll) % n);
    return(s.size() == v.size());
}
int main(){
    int t;
    cin >> t;
    while(t--){
        bool b = solve();
        if(b) cout << "YES\n";
        else cout << "NO\n";
    }
}
