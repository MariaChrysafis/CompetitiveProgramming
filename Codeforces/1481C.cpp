#include <iostream>
#include <vector>
#include <set>
using namespace std;
void solve(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> b(n);
    for(int i = 0; i < n; i++){
        cin >> a[i], a[i]--;
    }
    set<int> notEqual;
    set<int> s[n];
    for(int i = 0; i < n; i++){
        cin >> b[i], b[i]--;
        if(a[i] != b[i]){
            s[b[i]].insert(i);
            notEqual.insert(i);
        }
    }
    vector<int> c(m);
    for(int i = 0; i < m; i++){
        cin >> c[i], c[i]--;
    }
    int ind = -1;
    for(int i = 0; i < n; i++){
        if(b[i] == c[m - 1]){
            ind = i;
        }
    }
    if(ind == -1){
        cout << "NO\n";
        return;
    }
    int x = ind;
    vector<int> ans;
    for(int i = 0; i < m; i++){
        if(!s[c[i]].empty()){
            auto it = s[c[i]].begin();
            int v = *it;
            a[v] = c[i];
            s[c[i]].erase(it);
            notEqual.erase(v);
            ans.push_back(v + 1);
        }else if(!notEqual.empty()){
            auto it = notEqual.begin();
            int v = *it;
            a[v] = c[i];
            if(a[v] == b[v]) notEqual.erase(v);
            ans.push_back(v + 1);
        }else{
            a[x] = c[i];
            if(a[x] == b[x] && s[b[x]].count(x)){
                s[b[x]].erase(x);
                notEqual.erase(x);
            }
            if(a[x] != b[x] && !s[b[x]].count(x)){
                s[b[x]].insert(x);
                notEqual.insert(x);
            }
            ans.push_back(x + 1);
        }
    }
    for(int i = 0; i < n; i++){
        if(a[i] != b[i]){
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    for(int i: ans) cout << i << " ";
    cout << '\n';
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
