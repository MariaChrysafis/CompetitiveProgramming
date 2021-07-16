#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
 
using namespace std;
uint64_t gcd(uint64_t a, uint64_t b){
    if(min(a,b) == 0) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}
uint64_t lcm(uint64_t a, uint64_t b){
    return a/gcd(a,b) * b;
}
int main() {
    int n;
    cin >> n;
    vector<pair<uint64_t,uint64_t>> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i].first >> v[i].second;
    }
    uint64_t g = 0;
    for(int i = 0; i < n; i++){
        g = gcd(lcm(v[i].first, v[i].second), g);
    }
    if(g == 1){
        cout << -1 << endl;
        return 0;
    }
    for(long long i = sqrt(g); i >= 2; i--){
        if(g % i == 0){
            for(int j = 2; j < sqrt(i); j++){
                if(i % j == 0){
                    cout << j << endl;
                    return 0;
                }
            }
            cout << i << endl;
            return 0;
        }
    }
    cout << g << endl;
}
