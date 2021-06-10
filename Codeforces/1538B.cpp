#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
int find_ind(vector<int> v, int x){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == x) return i;
    }
}
int best(int n, int ind){
    return min(ind + 1, n - ind);
}
int solve(){
    int n;
    cin >> n;
    vector<long long> v(n);
    long long sum = 0;
    for(int i = 0; i < n; i++) cin >> v[i], sum += v[i];
    if(sum % n != 0){
        return -1;
    }   
    long long average = sum / n;
    int cnt = 0;
    for(int i = 0; i < n; i++){
        if(v[i] > average){
            cnt++;
        }
    }
    return cnt;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin >> q;
    while(q--){
        int x = solve();
        cout << x << endl;
    }
}
