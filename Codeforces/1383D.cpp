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
vector<T> readVector(int n) {
    vector<T> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    return v;
}

template<typename T>
void printVector(vector<T> vec) {
    for (T x: vec) {
        cout << x << " ";
    }
    cout << endl;
}

template<typename T>
void printVectorVector(vector<vector<T>> vec) {
    for (vector<T> x: vec) {
        //cout << x << " ";
        printVector(x);
    }
    cout << endl;
}

long long powr(long long x) {
    long long cur = 1;
    while (x--) {
        cur *= 2;
    }
    return cur;
}

string to_string(char c){
    string s = "";
    s += c;
    return s;
}

const int MOD = 1e9 + 7;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> arr(n);
    for(int i = 0; i < n; i++){
        arr[i].resize(m);
    }
    vector<int> row_max(n);
    vector<int> col_max(m);
    for(int i = 0; i < m; i++) {
        col_max[i] = 0;
    }
    for(int i = 0; i < n; i++) {
        row_max[i] = 0;
        for(int j = 0; j < m; j++) {
            cin >> arr[i][j];
            row_max[i] = max(row_max[i], arr[i][j]);
            col_max[j] = max(col_max[j], arr[i][j]);
        }
    }
    sort(row_max.begin(), row_max.end());
    sort(col_max.begin(), col_max.end());
    map<int, bool> isRow;
    map<int, bool> isCol;
    set<int> s;
    for(int i = 0; i < row_max.size(); i++) isRow[row_max[i]] = true, s.insert(row_max[i]);
    for(int i = 0; i < col_max.size(); i++) isCol[col_max[i]] = true, s.insert(col_max[i]);
    vector<int> vec;
    for(int i: s) vec.push_back(i);
    reverse(vec.begin(), vec.end());
    vector<vector<int>> new_arr(n);
    for(int i = 0; i < n; i++) {
        new_arr[i].resize(m);
    }
    int prevX = 0;
    int prevY = 0;
    //cout << isCol[11] << endl;
    new_arr[prevX][prevY] = vec[0];
    for(int i = 1; i < vec.size(); i++) {
        if(isCol[vec[i]]){
            prevY++;
        }
        if(isRow[vec[i]]){
            prevX++;
        }
        //cout << prevX << " " << prevY << " " << vec[i] << endl;
        new_arr[prevX][prevY] = vec[i];
    }
    queue<pair<int,int>> q;
    int x = -1;
    int y = -1;
    //cout << isRow[11] << endl;
    for(int i = n * m; i >= 1; i--) {
        x += isRow[i];
        y += isCol[i];
        //cout << x << " " << y << endl;
        if(!isRow[i] && !isCol[i]) {
            new_arr[q.front().first][q.front().second] = i;
            q.pop();
        }
        //cout << "YES\n";
        if(isRow[i] && y != 0) {
            for(int j = y - 1; j >= 0; j--){
                q.push({x, j});
            }
        }
        if(isCol[i] && x != 0) {
            for(int j = x - 1; j >= 0; j--){
                q.push({j, y});
            }
        }
    }
    printVectorVector<int>(new_arr);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
