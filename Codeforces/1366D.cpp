#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;
const long long MAX = 1e7 + 3;
vector<long long> primes(MAX);
long long gcd(long long a, long long b){
    if(min(a,b) == 0) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}
long long largestPowr(long long n, long long x){
    long long powr = 1;
    while(n % powr == 0){
        powr *= x;
    }
    return powr/x;
}
void solve(){
    int n;
    cin >> n;
    vector<pair<long long,long long>> v;
    vector<long long> vec;
    for(int i = 0; i < n; i++){
        long long x;
        cin >> x;
        vec.push_back(x);
        while(x > 0){
            if(primes[x] != x && primes[x] != 0){
                x /= primes[x];
            }else{
                break;
            }
        }
        x = largestPowr(vec.back(), x);
        v.push_back({x, vec.back()/x});
    }
    for(int i = 0; i < v.size(); i++){
        pair<int,int> p = v[i];
        if(gcd(p.first + p.second, vec[i]) != 1 || p.first == 1 || p.second == 1){
            v[i].second = v[i].first = -1;
        }
        //cout << p.first << " " << p.second << endl;
    }
    for(int i = 0; i < v.size(); i++) cout << v[i].first << " ";
    cout << endl;
    for(int i = 0; i < v.size(); i++) cout << v[i].second << " ";
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for(int i = 2; i < MAX; i++){
        if(primes[i] == 0){
            for(int j = i; j < MAX; j += i){
                primes[j] = i;
            }
        }
    }
    solve();
}
