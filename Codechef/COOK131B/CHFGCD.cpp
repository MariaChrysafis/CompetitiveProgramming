#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#include <array>

#define ll long long
#define endl '\n'

using namespace std;
long long gcd(long long a, long long b){
    if(min(a,b) == 0) return max(a,b);
    else return gcd(max(a,b) % min(a,b), min(a,b));
}
long long solve(long long x, long long y){
    long long ans = 3;
    for(int i = 0; i <= 1; i++){
        for(int j = 0; j <= 1; j++){
            if(gcd(x + i, y + j) != 1) ans = min(ans, (long long)i + j);
        }
    }
    return ans;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        long long x, y;
        cin >> x >> y;
        cout << solve(x, y) << endl;
    }
}
