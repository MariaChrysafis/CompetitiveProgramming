#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <set>
#define ll long long
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
int find_index(vector<int> v, int val){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == val){
            return i;
        }
    }
    return -1;
}
vector<int> reverse(vector<int> v, int pref){
    cout << pref + 1 << " ";
    reverse(v.begin(), v.begin() + pref + 1);
    return v;
}
void solve(){
    int n;
    cin >> n;
    vector<int> v(n);
    int cntr = 0;
    for(int i = 0; i < n; i++) {
        cin >> v[i];
        if(v[i] == i + 1){
            cntr++;
        }
    }
    cout << cntr << endl;
}
int main(){
    solve();
}
