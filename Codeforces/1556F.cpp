#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define ll long long
 
using namespace std;
 
const int MOD = 1e9 + 7;
vector<int> generateSubsets(int x){
    vector<int> ans;
    for(int s = x; s; s = (s - 1) & x){
        ans.push_back(s);
    }
    ans.push_back(0);
    return ans;
}
 
int h[14][(1 << 14)];
 
long long mult(long long x, long long y){
    return (x * y) % MOD;
}
 
long long binPow(long long a, long long b){
    long long ans = 1;
    long long res = a;
    while(b > 0){
        if(b & 1){
            ans = mult(res, ans);
        }
        res = mult(res, res);
        b /= 2;
    }
    return ans;
}
 
long long inv(long long x){
    return binPow(x, MOD - 2);
}
 
vector<int> a;
 
long long compute_h(long long x, long long y){
    //x beats everyone in y
    if((1 << x) & y){
        //cout << "YES\n";
        return 0;
    }
    long long ans = 1;
    for(int i = 0; i < a.size(); i++){
        if(y & (1 << i)){
            //cout << a[x] << " " << inv(a[x] + a[i]) << endl;
            ans = mult(ans, mult(a[x], inv(a[x] + a[i])));
        }
    }
    return ans;
}
 
long long G(int X, int Y){
    long long ans = 1;
    for(int i = 0; i < a.size(); i++){
        if(X & (1 << i)) {
            ans = mult(ans, h[i][Y]);
        }
    }
    return ans;
}
 
void print(vector<int> v){
    for(int i: v) cout << i << " ";
    cout << endl;
}
 
void print(vector<vector<int>> v){
    for(vector<int> i: v) {
        print(i);
    }
    cout << endl;
}
 
vector<int> dp_P;
 
long long P(int winners){
    if(__builtin_popcount(winners) <= 1){
        dp_P[winners] = 1;
        return 1;
    }
    if(dp_P[winners] != -1){
        return dp_P[winners];
    }
    long long ans = 0;
    for(int sub: generateSubsets(winners)){
        if(sub == winners || sub == 0) continue;
        ans += mult(P(sub), G(sub, winners - sub));
        ans %= MOD;
    }
    return (dp_P[winners] = (MOD + 1 - ans) % MOD);
}
 
long long teams = 0;
 
long long F(int winners){
    return mult(P(winners), G(winners, teams - winners));
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    a.resize(N);
    dp_P.resize((1 << N));
    for(int i = 0; i < dp_P.size(); i++){
        dp_P[i] = -1;
    }
    for(int i = 0; i < N; i++){
        cin >> a[i];
        teams += (1 << i);
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < (1 << N); j++){
            h[i][j] = compute_h(i, j); //i beats everyone in j
            //cout << h[i][j] << " ";
        }
        //cout << endl;
    }
    long long ans = 0;
    for(int winners: generateSubsets(teams)){
        ans += mult(__builtin_popcount(winners), F(winners));
        ans %= MOD;
    }
    cout << ans << endl;
}
