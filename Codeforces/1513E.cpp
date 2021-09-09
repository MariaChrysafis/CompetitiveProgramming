#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define ll long long

using namespace std;
const int MOD = 1e9 + 7;

long long mult(long long a, long long b){
    return (a * b) % MOD;
}

long long binPow(long long a, long long b){
    long long ans = 1;
    long long res = a;
    while(b > 0){
        if(b & 1){
            ans = mult(ans, res);
        }
        res = mult(res, res);
        b /= 2;
    }
    return ans;
}

long long inv(long long x){
    return binPow(x, MOD - 2);
}

vector <long long> fact;

long long combo(long long x, long long y){
    return mult(fact[x], inv(mult(fact[y], fact[x - y])));
}

long long rearrange(vector<long long> v){
    map<int,int> oc;
    for(int i: v) oc[i]++;
    long long ans = fact[v.size()];
    for(pair<int,int> p: oc){
        ans = mult(ans, inv(fact[p.second]));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fact = {1};
    while(fact.size() != 1e5 + 10){
        fact.push_back(mult(fact.size(), fact.back()));
    }
    int n;
    cin >> n;
    vector<long long> v(n);
    long long sum = 0;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        sum += v[i];
    }
    if(sum % n != 0){
        cout << 0;
        return 0;
    }
    vector<long long> left;
    vector<long long> right;
    int mid = 0;
    for(int i = 0; i < n; i++){
        if(v[i] < sum/n){
            left.push_back(v[i]);
        }else if(v[i] > sum/n){
            right.push_back(v[i]);
        }else{
            mid++;
        }
    }
    //cout << left.size() << " " << right.size() << endl;
    if(left.size() <= 1 || right.size() <= 1){
        cout << rearrange(v);
        return 0;
    }
    long long ans = mult(combo(n, mid), mult(rearrange(left), rearrange(right)));
    ans = mult(ans, 2);
    cout << ans << endl;
}
