#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>
 
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
 
void solve() {
    long long n;
    cin >> n;
    if(n % 3 == 0){
        cout << n/3 << " " << n/3 << endl;
        return;
    }else if(n % 3 == 1){
        cout << (n + 4)/3 << " " << (n -1)/3 << endl;
    }else{
        cout << (n - 1)/3 << " " << (n + 2)/3 << endl;
    }
}
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
