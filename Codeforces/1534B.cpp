#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>
#include <stack>
#include <map>
using namespace std;
void print(vector<long long> v){
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}
long long cost(vector<long long> v){
    if(v.size() == 1) return v[0];
    long long cntr = v[0] + v[v.size() - 1];
    for(int i = 1; i < v.size(); i++){
        cntr += abs(v[i] - v[i - 1]);
    }
    return cntr;
}
long long change(vector<long long> v1, vector<long long> v2){
    long long cntr = 0;
    for(int i = 0; i < v1.size(); i++){
        cntr += abs(v1[i] - v2[i]);
    }
    return cntr;
}
vector<long long> fill(vector<long long> v, int x){
    for(int i = 0; i < v.size(); i++){
        v[i] = x;
    }
    return v;
}
long long slv(vector<long long> arr, bool b1, bool b2){
    int n = arr.size();
    vector<long long> suf(arr.size());
    for(int i = 0; i < n; i++){
        suf[i] = arr[i];
    }
    if(b1) suf[0] = min(arr[0], arr[1]);
    if(b2) suf[suf.size() - 1] = min(arr[arr.size() - 1], arr[arr.size() - 2]);
    for(int i = 1; i < n - 1; i++){
        suf[i] = arr[i];
        if(arr[i] > arr[i - 1] && arr[i] > arr[i + 1]){
            suf[i] = max(arr[i - 1], arr[i + 1]);
        }
    }
    if(!b1) suf[0] = min(arr[0], arr[1]);
    if(!b2) suf[arr.size() - 1] = min(arr[arr.size() - 1], arr[arr.size() - 2]);
    long long ans = change(suf, arr) + cost(suf);
    return ans;
}
long long slv1(vector<long long> arr, bool b1, bool b2){
    int n = arr.size();
    vector<long long> suf(arr.size());
    for(int i = 0; i < n; i++){
        suf[i] = arr[i];
    }
    if(b1) suf[0] = min(arr[0], arr[1]);
    if(b2) suf[suf.size() - 1] = min(arr[arr.size() - 1], arr[arr.size() - 2]);
    for(int i = 1; i < n - 1; i++){
        suf[i] = arr[i];
        if(arr[i] > suf[i - 1] && arr[i] > arr[i + 1]){
            suf[i] = max(suf[i - 1], arr[i + 1]);
        }
    }
    if(!b1) suf[0] = min(arr[0], arr[1]);
    if(!b2) suf[arr.size() - 1] = min(arr[arr.size() - 1], arr[arr.size() - 2]);
    long long ans = change(suf, arr) + cost(suf);
    return ans;
}
long long slv2(vector<long long> arr, bool b1, bool b2){
    int n = arr.size();
    vector<long long> suf(arr.size());
    for(int i = 0; i < n; i++){
        suf[i] = arr[i];
    }
    if(b1) suf[0] = min(arr[0], arr[1]);
    if(b2) suf[suf.size() - 1] = min(arr[arr.size() - 1], arr[arr.size() - 2]);
    for(int i = 1; i < n - 1; i++){
        suf[i] = arr[i];
        if(arr[i] > arr[i - 1] && arr[i] > suf[i + 1]){
            suf[i] = max(suf[i - 1], suf[i + 1]);
        }
    }
    if(!b1) suf[0] = min(arr[0], arr[1]);
    if(!b2) suf[arr.size() - 1] = min(arr[arr.size() - 1], arr[arr.size() - 2]);
    long long ans = change(suf, arr) + cost(suf);
    return ans;
}
long long slv3(vector<long long> arr, bool b1, bool b2){
    int n = arr.size();
    vector<long long> suf(arr.size());
    for(int i = 0; i < n; i++){
        suf[i] = arr[i];
    }
    if(b1) suf[0] = min(arr[0], arr[1]);
    if(b2) suf[suf.size() - 1] = min(arr[arr.size() - 1], arr[arr.size() - 2]);
    for(int i = 1; i < n - 1; i++){
        suf[i] = arr[i];
        if(arr[i] > suf[i - 1] && arr[i] > suf[i + 1]){
            suf[i] = max(suf[i - 1], suf[i + 1]);
        }
    }
    if(!b1) suf[0] = min(arr[0], arr[1]);
    if(!b2) suf[arr.size() - 1] = min(arr[arr.size() - 1], arr[arr.size() - 2]);
    long long ans = change(suf, arr) + cost(suf);
    return ans;
}
void solve(){
    int n;
    cin >> n;
    vector<long long> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    long long myMin = min(min(slv(arr, 0, 1), slv(arr, 1, 0)), min(slv(arr, 0, 0), slv(arr, 1, 1)));
    long long myMin1 = min(min(slv1(arr, 0, 1), slv1(arr, 1, 0)), min(slv1(arr, 0, 0), slv1(arr, 1, 1)));
    long long myMin2 = min(min(slv2(arr, 0, 1), slv2(arr, 1, 0)), min(slv2(arr, 0, 0), slv2(arr, 1, 1)));
    long long myMin3 = min(min(slv3(arr, 0, 1), slv3(arr, 1, 0)), min(slv3(arr, 0, 0), slv3(arr, 1, 1)));
    cout << min(min(myMin, myMin1), min(myMin2, myMin3)) << endl;
 
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
