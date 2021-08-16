#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
using namespace std;
bool solve(){
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    vector<int> q = v;
    sort(q.begin(), q.end());
    map<int,int> oc;
    for(int i = 0; i < n; i++){
        oc[q[i]] = i;
    }
    for(int i = 0; i < n; i++){
        v[i] = oc[v[i]];
        //cout << v[i] << " ";
    }
    //cout << endl;
    oc.clear();
    for(int i = 0; i < n; i++){
        oc[v[i]] = i;
    }
    int cntr = 1;
    for(int i = 0; i < n - 1; i++){
        if(v[i] != v[i + 1] - 1){
            cntr++;
        }
    }
    return (cntr <= m);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        bool b = solve();
        if(b){
            cout << "YES\n";
        }else{
            cout << "NO\n";
        }
    }
}
