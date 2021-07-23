#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>
#include <map>
#include <algorithm>
 
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
 
void print(vector<char> v){
    for(char c: v) {
        cout << c << " ";
    }
    cout << endl;
}
 
void print(vector<vector<int>> v){
    for(vector<int> vec: v){
        print(vec);
    }
    cout << endl;
}
 
void print(vector<vector<long long>> v){
    for(vector<long long> vec: v){
        print(vec);
    }
    cout << endl;
}
 
void print(vector<vector<char>> v){
    for(vector<char> vec: v){
        print(vec);
    }
    cout << endl;
}
int solve(int n, int m, int k) {
    if(n * m < 2 * k){
        return false;
    }
    if(m % 2 == 1){
        return solve(n, m - 1, k);
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
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        int b = solve(n, m, k);
        if(b == 1){
            cout << "YES\n";
        }else if(b == 0){
            cout << "NO\n";
        }else if(b == 2){
            cout << "MAYBE\n";
        }
    }
}
