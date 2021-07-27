#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
 
using namespace std;
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
int MEX(vector<int> v){
    map<int,bool> oc;
    for(int i: v) oc[i] = true;
    for(int i = 0; i < v.size() + 3; i++){
        if(!oc[i]){
            return i;
        }
    }
}
bool great(vector<int> v){
    map<int,bool> oc;
    for(int i: v) oc[i] = true;
    for(int i = 0; i < v.size(); i++){
        if(!oc[i]) return false;
    }
    return true;
}
bool increasing(vector<int> v){
    for(int i = 0; i < v.size() - 1; i++){
        if(v[i] > v[i + 1]){
            return false;
        }
    }
    return true;
}
void solve(){
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    vector<int> indices;
    for(int i = 0; i < 2 * n; i++){
        int x = MEX(v);
        if(x == n){
            for(int j = 0; j < n; j++){
                if(v[j] != j){
                    v[j] = x;
                    indices.push_back(j + 1);
                    break;
                }
            }
            continue;
        }
        v[x] = x;
        indices.push_back(x + 1);
        if(increasing(v)){
            break;
        }
    }
    cout << indices.size() << endl;
    print(indices);
}
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
