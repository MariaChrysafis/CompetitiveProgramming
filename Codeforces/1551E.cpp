#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
using namespace std;
void print(vector<int> v) {
    for (int i: v) {
        cout << i << " ";
    }
    cout << endl;
}
 
void print(vector<long long> v) {
    for (long long x: v) {
        cout << x << " ";
    }
    cout << endl;
}
 
void print(vector<char> v) {
    for (char c: v) {
        cout << c << " ";
    }
    cout << endl;
}
 
void print(vector<vector<int>> v) {
    for (vector<int> vec: v) {
        print(vec);
    }
    cout << endl;
}
 
void print(vector<vector<long long>> v) {
    for (vector<long long> vec: v) {
        print(vec);
    }
    cout << endl;
}
 
void print(vector<vector<char>> v) {
    for (vector<char> vec: v) {
        print(vec);
    }
    cout << endl;
}
 
vector<vector<int>> fill(int n, int m, int val) {
    vector<vector<int>> v;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        v[i].resize(m);
        for (int j = 0; j < m; j++) {
            v[i][j] = val;
        }
    }
    return v;
}
 
vector<int> read(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    return arr;
}
 
vector<long long> readll(int n) {
    vector<long long> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    return arr;
}
int min(vector<int> v){
    int myMin = INT_MAX;
    for(int i = 0; i < v.size(); i++){
        myMin = min(myMin, v[i]);
    }
    return myMin;
}
int max(vector<int> v){
    int myMax = -INT_MAX;
    for(int i = 0; i < v.size(); i++){
        myMax = max(myMax, v[i]);
    }
    return myMax;
}
const int INF = 1e9;
int main(){
    int t;
    cin >> t;
    while(t--) {
        int n, k;
        cin >> n >> k;
        vector<int> arr = read(n);
        vector<vector<int>> dp = fill(n, n + 1, -INF);
        dp[0][0] = 0;
        dp[0][1] = (arr[0] == 1);
        vector<int> ans;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= i + 1; j++) {
                if (j != 0) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + (arr[i] == j));
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                if(dp[i][j] >= k && i == n - 1){
                    //cout << i << " " << j << endl;
                }
            }
        }
        for(int j = 0; j <= n; j++){
            if(dp[n - 1][j] >= k) ans.push_back(n - j);
        }
        cout << ((min(ans) == INT_MAX) ? -1 : min(ans)) << endl;
    }
}
