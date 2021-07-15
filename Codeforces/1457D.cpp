#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
const long long MAX = 1e18;
void solve(){
    long long n, m;
    cin >> n >> m;
    vector<long long> inp1, inp2;
    for(int i = 0; i < n; i++){
        long long x;
        cin >> x;
        inp1.push_back(x);
    }
    for(int i = 0; i < n; i++){
        long long x;
        cin >> x;
        inp2.push_back(x);
    }
    vector<int> v1, v2;
    for(int i = 0; i < n; i++){
        if(inp2[i] == 2){
            v2.push_back(inp1[i]);
        }else{
            v1.push_back(inp1[i]);
        }
    }
    sort(v1.begin(), v1.end()), sort(v2.begin(), v2.end());
    reverse(v1.begin(), v1.end()), reverse(v2.begin(), v2.end());
    vector<long long> pref2, pref1;
    pref2.push_back(0), pref1.push_back(0);
    for(int i = 0; i < v2.size(); i++){
        pref2.push_back(pref2.back() + v2[i]);
    }
    for(int i = 0; i < v1.size(); i++){
        pref1.push_back(pref1.back() + v1[i]);
    }
    //print(pref1), print(pref2);
    long long myMin = MAX;
    for(int i = 0; i < pref1.size(); i++){
        long long l = 0;
        long long r = pref2.size() - 1;
        while(l < r){
            long long mid = (l + r)/2;
            if(pref2[mid] + pref1[i] >= m){
                r = mid;
            }else{
                l = mid + 1;
            }
        }
        if(pref2[l] + pref1[i] < m) continue;
        //cout << 2 * l + i << endl;
        myMin = min(2 * l + i, myMin);
    }
    if(myMin == MAX){
        cout << -1 << endl;
        return;
    }
    cout << myMin << endl;
}
int main() {
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
