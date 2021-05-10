#include <cmath>
#include <queue>
#include <iomanip>
#include <map>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef long long ll;
ll summand(vector<ll> v){
    ll summand1 = 0;
    for(ll x: v){
        summand1 += x;
    }
    return summand1;
}
void print(vector<ll> v){
    for(ll i: v){
        cout << i << " ";
    }
    cout << endl;
}
ll K, N, M;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> K >> N >> M;
    vector<ll> A(K);
    for(int i = 0; i < K; i++) cin >> A[i];
    vector<ll> B(K);
    for(int i = 0; i < K; i++){
        ll B2_i = A[i] * M/N;
        B[i] = B2_i;
    }
    if(summand(B) == M){
        print(B);
        return 0;
    }
    int ind = 1;
    vector<pair<int,int>> b_copy(K);
    for(int i = 0; i < K; i++){
        b_copy[i].second = i;
        b_copy[i].first = (B[i] * N - A[i] * M);
    }
    sort(b_copy.begin(), b_copy.end());
    int dif = abs(summand(B) - M);
    for(int i = 0; i < dif; i++){
        B[b_copy[i].second] += ind;
    }
    print(B);
    return 0;
}
