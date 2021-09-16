#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
#include <queue>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;

template<typename T>
T readVal() {
    T n;
    cin >> n;
    return n;
}

template<typename T>
vector<T> readVector(T n) {
    vector<T> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    return v;
}

template<typename T>
void printVector(vector<T> vec) {
    cout << "! ";
    for (T x: vec) {
        cout << x << " ";
    }
    cout << endl;
}

vector<int> secretArray = {0, 0, 2, 3};

int queryAnd(int i, int j){
    cout << "AND" << " " << i + 1 << " " << j + 1 << '\n';
    cout.flush();
    int x; cin >> x; return x;
    return (secretArray[i] & secretArray[j]);
}

int queryOr(int i, int j){
    cout << "OR" << " " << i + 1 << " " << j + 1 << '\n';
    cout.flush();
    int x; cin >> x; return x;
    return (secretArray[i] | secretArray[j]);
}

int queryXor(int i, int j){
    cout << "XOR" << " " << i + 1 << " " << j + 1 << '\n';
    cout.flush();
    int x; cin >> x; return x;
    return (secretArray[i] ^ secretArray[j]);
}

vector<int> changeBit(int x, vector<int> ans){
    for(int i = 0; i < ans.size(); i++){
        if(ans[i] & (1 << x)){
            ans[i] -= (1 << x);
        } else {
            ans[i] += (1 << x);
        }
    }
    return ans;
}

void solve() {
    int n = secretArray.size();
    cin >> n;
    vector<int> ans(n);
    map<int,int> oc;
    ans[0] = 0;
    oc[0] = 0;
    for(int i = 1; i < n; i++) {
        ans[i] = queryXor(0, i);
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ans[i] == ans[j]) {
                int a = queryAnd(i, j);
                for(int k = 0; k < 32; k++){
                    if((a & (1 << k)) != (ans[i] & (1 << k))) {
                        ans = changeBit(k, ans);
                    }
                }
                printVector<int>(ans);
                return;
            }
        }
    }
    for(int i = 1; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if((ans[i] & ans[j]) == 0 && (ans[i] ^ ans[j]) == n - 1){
                int a = queryAnd(i, 0);
                int b = queryAnd(j, 0);
                for(int k = 0; k < 32; k++){
                    if((a & (1 << k))){
                        ans = changeBit(k, ans);
                    }
                    if(b & (1 << k)){
                        ans = changeBit(k, ans);
                    }
                }
                printVector<int>(ans);
                return;
            }
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
