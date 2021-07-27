#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
 
#define ll long long
 
using namespace std;
void print(vector<bool> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    vector<bool> vec;
    for(int i = 0; i < n - 1; i++){
        if(v[i] < v[i + 1]){
            vec.push_back(0);
        }else{
            vec.push_back(1);
        }
    }
    //print(vec);
    int cur = vec[0];
    int soFar = 0;
    vector<int> ans;
    vector<bool> key;
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] == cur){
            soFar++;
        }else{
            ans.push_back(soFar);
            key.push_back(cur);
            soFar = 1;
            cur = vec[i];
        }
    }
    if(soFar != 0) ans.push_back(soFar), key.push_back(cur);
    //print(ans), print(key);
    int myMax = 0;
    for(int i = 0; i < ans.size(); i++) {
        myMax = max(myMax, ans[i]);
    }
    int cntr = 0;
    for(int i = 0; i < ans.size(); i++){
        if(ans[i] == myMax) {
            if((i > 0 && ans[i - 1] == myMax) || (i + 1 < ans.size() && ans[i + 1] == myMax)) continue;
            cntr++;
        }
    }
    int oc = 0;
    for(int i = 0; i < ans.size(); i++){
        if(ans[i] == myMax) oc++;
    }
    if(cntr > 1 || oc >= 3){
        cout << 0;
        return 0;
    }
    for(int i = 0; i < ans.size() - 1; i++){
        if(ans[i] == ans[i + 1] && ans[i] == myMax && ans[i] % 2 == 0 && key[i] == 0){
            cout << 1 << endl;
            return 0;
        }
    }
    cout << 0 << endl;
}
