
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
#define ll long long
using namespace std;
vector<ll> diagonal;
pair<int,int> solve() {
    ll n;
    cin >> n;
    for(int i = 0; i < diagonal.size() - 1; i++){
        if(n == diagonal[i]){
            return {i + 1, i + 1};
        }
        if(n == (i + 1) * (i + 1)){
            return {i + 1, 1};
        }
        if(n == i * i + 1){
            return {1, i + 1};
        }
    }
    for(int i = 0; i < diagonal.size() - 1; i++){
        if(n > diagonal[i] && n < (i + 1) * (i + 1)){
            return {i + 1, (i + 1) * (i + 1) - n + 1};
        }
        if(n < diagonal[i] && n > i * i){
            return {n - i * i, i + 1};
        }
    }
    return {-1, -1};
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for(int i = 1; i < 1e9; i++){
        diagonal.push_back(i * i - i + 1);
        if(diagonal.back() >= 2e9){
            break;
        }
    }
    int t;
    cin >> t;
    while(t--){
        pair<int,int> p = solve();
        cout << p.first << " " << p.second << endl;
    }
}
