#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
vector<string> v;
int dif(string a, string b){
    int cntr = 0;
    for(int i = 0; i < a.length(); i++){
        if(a[i] != b[i]){
            cntr++;
        }
    }
    return cntr;
}
bool valid(string k){
    for(string s: v){
        if(dif(s, k) >= 2){
            return false;
        }
    }
    return true;
}
string change(string s, int x, char c){
    s[x] = c;
    return s;
}
void solve(){
    int n, m;
    cin >> n >> m;
    v.resize(n);
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        v[i] = s;
    }
    sort(v.begin(), v.end());
    swap(v[0], v[v.size() - 1]);
    if(v[0] == v[v.size() - 1]){
        cout << v[0] << endl;
        return;
    }
    vector<int> pos;
    for(int i = 0; i < m; i++){
        if(v[0][i] != v[v.size() - 1][i]){
            pos.push_back(i);
        }
    }
    if(pos.size() >= 3){
        cout << -1 << '\n';
        return;
    }
    if(pos.size() == 1){
        for(char c = 'a'; c <= 'z'; c++){
            string key = change(v[0], pos[0], c);
            if(valid(key)){
                cout << key << endl;
                return;
            }
        }
    }else{
        for(char c = 'a'; c <= 'z'; c++){
            for(char c1 = 'a'; c1 <= 'z'; c1++){
                string key = change(v[0], pos[0], c);
                key = change(key, pos[1], c1);
                if(valid(key)){
                    cout << key << endl;
                    return;
                }
            }
        }
    }
    cout << -1 << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
