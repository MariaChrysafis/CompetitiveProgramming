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
        cout << c;
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
vector<vector<char>> tile(int n, int m, int k){
    vector<vector<char>> v;
    v.resize(n);
    //initialize to z
    for(int i = 0; i < n; i++){
        v[i].resize(m);
        for(int j = 0; j < m; j++){
            v[i][j] = 'z';
        }
    }
    //horizontally place some tiles ('a' - 'f')
    char cur = 'a';
    for(int i = 0; i < n - 1; i += 2){
        for(int j = 0; j < m - 1; j += 2){
            if(k == 0) break;
            while((i - 1 >= 0 && v[i - 1][j] == cur)
            || (j - 1 >= 0 && v[i][j - 1] == cur)){
                cur++;
                if(cur == 'x') cur = 'a';
            }
            v[i][j] = v[i][j + 1] = cur;
            cur++, k--;
            if(k == 0) break;
            if(cur == 'x') cur = 'a';
            v[i + 1][j] = v[i + 1][j + 1] = cur;
            cur++, k--;
            if(cur == 'x') cur = 'a';
            if(k == 0) break;
        }
    }
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < m; j++){
            if(v[i][j] == 'z' && v[i + 1][j] == 'z'){
                // (i, j + 1)
                // (i, j - 1)
                // (i + 1, j + 1)
                // (i + 1, j - 1)
                // (i + 2, j)
                // (i - 1, j)
                while((j + 1 < m && v[i][j + 1] == cur)
                || (j > 0 && v[i][j - 1] == cur)
                || (j + 1 < m && v[i + 1][j + 1] == cur)
                || (j > 0 && v[i + 1][j - 1] == cur)
                || (i > 0 && v[i - 1][j] == cur)
                || (i + 2 < n && v[i + 2][j] == cur)){
                    cur++;
                    if(cur == 'x') cur = 'a';
                }
                v[i][j] = v[i + 1][j] = cur;
                cur++;
                if(cur == 'x') cur = 'a';
            }
        }
    }
    return v;
}
bool valid(int n, int m, int k) {
    if(n * m < 2 * k){
        return false;
    }
    if(m % 2 == 1){
        return valid(n, m - 1, k);
    }
    if(n % 2 == 1){
        if(k < m/2){
            return false;
        }
    }
    if(n % 2 == 0) {
        return (k % 2 == 0);
    }
    if(n % 2 == 1){
        return ((m/2) % 2 == k % 2);
    }
}
vector<vector<char>> ans(int n, int m, int k){
    if(n % 2 == 0 && m % 2 == 0){
        return tile(n, m, k);
    }else if(m % 2 == 1){
        char c = 'y';
        vector<vector<char>> ans = tile(n, m - 1, k);
        for(int i = 0; i < ans.size(); i++) {
            ans[i].push_back(c);
            if(i % 2 == 1){
                c++;
                if(c > 'z') c = 'y';
            }
        }
        return ans;
    }else{
        return ans(m, n, n * m/2 - k);
    }
}
vector<vector<char>> transpose(vector<vector<char>> v){
    int n = v.size();
    int m = v[0].size();
    vector<vector<char>> v1(m);
    for(int i = 0; i < m; i++){
        v1[i].resize(n);
        for(int j = 0; j < n; j++){
            v1[i][j] = v[j][i];
        }
    }
    return v1;
}
void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    if(valid(n, m, k)){
        cout << "YES\n";
    }else{
        cout << "NO\n";
        return;
    }
    vector<vector<char>> v;
    v.resize(n);
    for(int i = 0; i < n; i++){
        v[i].resize(m);
        for(int j = 0; j < m; j++){
            v[i][j] = 'z';
        }
    }
    if(ans(n, m, k).size() != n && ans(n, m, k)[0].size() != m){
        print(transpose(ans(n,m, k)));
    }else {
        print(ans(n, m, k));
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
