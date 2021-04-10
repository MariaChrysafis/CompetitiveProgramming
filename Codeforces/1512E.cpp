#include <iostream>
#include <map>
#include <cmath>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;
bool valid(int k, int length, int s){
    //k + (k - 1) + (k - 2) + ... + (k - (n - 1))
    //nk - n * (n - 1) /2
    int ans = k + length * (length - 1)/2;
    return (ans <= s);
}
int binSearch(int left, int right, int length, int s){
    if(right < left){
        return -1;
    }
    //cout << left << " " << right << endl;
    if(left == right){
        return left;
    }
    int mid = (left + right + 1)/2;
    if(valid(mid, length, s)){
        return binSearch(mid, right, length, s);
    }else{
        return binSearch(left, mid - 1, length, s);
    }
}
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
void solve(){
    int n, l, r, s;
    cin >> n >> l >> r >> s;
    int orig = s;
    int o = n;
    int length = r - l + 1;
    l--;
    r--;
    vector<int> v;
    for(int i = 0; i < length; i++){
        int x = binSearch(1, n, length - i, s);
        v.push_back(x);
        if(x == -1){
            cout << -1 << endl;
            return;
        }
        s -= x;
        n = x - 1;
    }
    n = o;
    //print(v);
    int sum = 0;
    for(int i: v){
        sum += i;
    }
    if(sum != orig){
        cout << -1 << endl;
        return;
    }
    map<int,bool> myMap;
    vector<int> arr(n);
    for(int i = 0; i < v.size(); i++){
        myMap[v[i]] = true;
        arr[l + i] = v[i];
    }
    //print(arr);
    //print(v);
    int x = 1;
    for(int i = 0; i < l; i++){
        while(myMap[x]){
            x++;
        }
        arr[i] = x;
        myMap[x] = true;
    }
    for(int i = r + 1; i < n; i++){
        while(myMap[x]){
            x++;
        }
        arr[i] = x;
        myMap[x] = true;
    }
    for(int i: arr){
        cout << i << " ";
    }
    cout << endl;
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
