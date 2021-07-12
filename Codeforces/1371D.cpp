#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
#include <queue>
#include <set>
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i;
    }
    cout << endl;
}
void print(vector<bool> v){
    for(bool i: v){
        cout << i;
    }
    cout << endl;
}
string yesNo(bool b){
    if(b) return "YES";
    return "NO";
}
vector<int> shift(vector<int> v){
    vector<int> vec;
    vec.push_back(v[v.size() - 1]);
    for(int i = 0; i < v.size() - 1; i++){
        vec.push_back(v[i]);
    }
    return vec;
}
void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> base;
    int cntr = 0;
    for(int i = 0; i < (k - (k % n))/n; i++){
        base.push_back(1);
        cntr++;
    }
    while(base.size() != n){
        base.push_back(0);
    }
    reverse(base.begin(), base.end());
    vector<vector<int>> v;
    int soFar = 0;
    for(int i = 0; i < n; i++){
        v.push_back(base);
        base = shift(base);
        soFar += cntr;
    }
 
    for(int i = 0; i < k - soFar; i++){
        v[i][i] = 1;
    }
    int miRow = 1e9;
    int maRow = 0;
    for(int i = 0; i < n; i++){
        int r = 0;
        for(int j = 0; j < n; j++){
            if(v[i][j]){
                r++;
            }
        }
        miRow = min(miRow, r);
        maRow = max(maRow, r);
    }
    cout << pow(maRow - miRow,2) * 2 << '\n';
    for(vector<int> vec: v){
        print(vec);
    }
}
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
