#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <map>
#define ll long long
using namespace std;
void print(vector<int> v){
    for(int i: v){
        cout << i << " ";
    }
    cout << endl;
}
void print(vector<long long> v){
    for(long long i: v){
        cout << i << " ";
    }
    cout << endl;
}
int gcd(int a, int b){
    if(min(a,b) == 0) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}
void solve(){
    int n;
    cin >> n;
    cout << 2 << " " << n - 1 << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
