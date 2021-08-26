#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#include <queue>

#define ll long long
using namespace std;
#define P(x, y) make_pair(x,y)
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
vector<string> pos;
void rec(string s, int x){
    if(s.length() == x){
        bool valid = false;
        for(char c: s){
            if(c == '1'){
                valid = true;
            }
        }
        if(valid) pos.push_back(s);
        return;
    }
    rec(s + '1', x);
    rec(s + '0', x);
}
bool solve(){
    int n;
    cin >> n;
    vector<int> v(n);
    int cntr = 0;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        if(abs(v[i]) >= 2){
            cntr++;
        }
    }
    if(cntr >= 2){
        return false;
    }
    vector<int> temp;
    map<int,int> oc;
    for(int i = 0; i < n; i++) {
        //s.insert(v[i]);
        if (oc[v[i]] <= 1) {
            temp.push_back(v[i]);
        }
        oc[v[i]]++;
    }
    v = temp;
    rec("", v.size());
    for(string key: pos){
        int prod = 1;
        for(int i = 0; i < key.size(); i++){
            if(key[i] == '1'){
                prod *= v[i];
            }
        }
        if(oc[prod] == 0) return false;
    }
    return true;
}
int main() {
    int t;
    cin >> t;
    while(t--){
        bool b = solve();
        cout << b << '\n';
    }
}
