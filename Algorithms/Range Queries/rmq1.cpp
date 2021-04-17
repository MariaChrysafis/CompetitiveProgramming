#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
vector<vector<int>> dp;
vector<int> arr;
const int INF = 1;
int minI(int left, int length){
    //length is actually log2(length)
    if(left + pow(2,length) - 1 >= arr.size()) return -INF;
    if(dp[left][length] != -1){
        return dp[left][length];
    }
    if(length == 0){
        dp[left][length] = arr[left];
        return dp[left][length];
    }
    int l = minI(left,length - 1);
    int r = minI(left + pow(2,length - 1), length - 1);
    dp[left][length] = min(l, r);
    return dp[left][length];
}
int query(int l, int r){
    //minimum from l to r
    int length = log2(r - l + 1);
    //cout << length << endl;
    return min(dp[l][length], dp[r - pow(2,length) + 1][length]);
}
int main(){
    int n;
    cin >> n;
    arr.resize(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    //cout << "TES" << endl;
    //precompute
    dp.resize(n);
    for(int i = 0; i < n; i++){
        dp[i].resize(log2(n) + 2); //buffer
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < dp[i].size(); j++){
            dp[i][j] = -1;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < dp[i].size(); j++){
            dp[i][j] = minI(i, j);
            //cout << dp[i][j] << " ";
        }
        //cout << endl;
    }
    //cout << "YES" << endl;
    int q;
    cin >> q;
    while(q--){
        int l, r;
        cin >> l >> r;
        //l--, r--;
        int x = query(l, r);
        cout << x << endl;
    }
}
