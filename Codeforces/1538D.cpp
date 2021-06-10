#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
bool perfectSquare(int n){
    int x = sqrt(n);
    return (x * x == n);
}
bool isPrime(int x){
    if(x == 1) return false;
    for(int i = 2; i <= sqrt(x); i++) if(x % i == 0) return false;
    return true;    
}
long long powers(long long n, long long p){
    int cntr = 0;
    while(n % p == 0){
        cntr++;
        n /= p;
    }
    return cntr;
}
vector<bool> create(int SZ){
    vector<bool> prime(SZ);
    for(int i = 0; i < SZ; i++){
        prime[i] = true;
    }
    prime[1] = false;
    prime[2] = true;
    for(int i = 2; i < SZ; i++){
        if(!prime[i]) continue;
        for(int j = 2 * i; j < SZ; j += i){
            prime[j] = false;
        }
    }
    return prime;
}
vector<bool> prime;
map<int,int> ans;
long long factors(long long n){
    if(ans[n] != 0) return ans[n];
    if(n == 1) return 0;
    int x = 0;
    if(isPrime(n)) return 1;
    int y = n;
    for(int i = 2; i <= sqrt(n) + 3; i++){
        if(n % i == 0 && prime[i]){
            x += powers(n, i);
            y /= pow(i, powers(n, i));
        }
        if(i > sqrt(y) + 3) break;
    }
    if(isPrime(y)) x ++;
    ans[n] = x;
    return x;
}
long long GCD(long long a, long long b){
    if(min(a,b) == 0){
        return max(a, b);
    }
    return GCD(max(a,b) % min(a,b), min(a,b));
}
bool solve(){
    //cout << factors(4) << endl;
    long long a, b, k;
    cin >> a >> b >> k;
    long long atMost = factors(a) + factors(b);
    if(k > atMost){
        return false;
    }
    if(a == b) return (k >= 2);
    if(a == 1 || b == 1){
        return (k >= 1);
    }
    if(GCD(a,b) == min(a,b)) return (k >= 1);
    else return (k >= 2);
}
int main(){
    prime = create(100000);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        bool b = solve();
        if(b){
            cout << "YES\n";
        }else{
            cout << "NO\n";
        }
    }
}
