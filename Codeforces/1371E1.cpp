#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
 
#define ll long long
 
using namespace std;
int n, p;
vector<int> v;
bool valid(int x){
    //x ... x + n - 1
    long long pos = 1;
    long long soFar = 0;
    for(int i = n - 1; i >= 0; i--){
        if(x + n - v[i] - soFar < 0) {
            return p - 1;
        }
        if(v[i] < x) {
            if((n - soFar) % p == 0){
                return false;
            }
        }else {
            if((x + n - v[i] - soFar) % p == 0){
                return false;
            }
            //pos *= (x + n - v[i] - soFar);
        }
        soFar++;
    }
    return true;
}
int main(){
    cin >> n >> p;
    v.resize(n);
    int myMax = 0;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        myMax = max(myMax, v[i]);
    }
    sort(v.begin(), v.end());
    vector<int> ans;
    for(int i = myMax - n; i <= myMax; i++){
        if(valid(i)){
            ans.push_back(i);
        }
    }
    cout << ans.size() << endl;
    for(int i: ans) cout << i << ' ';
    cout << endl;
 
}
