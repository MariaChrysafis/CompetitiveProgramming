#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
#include <set>
 
using namespace std;
vector<long long> ans;
vector<long long> powr;
void memoize(long long n, long long k, long long cntr) {
    if (n == 0) {
        return;
    }
    long long ploss = 0;
    long long best = 0;
    long long loss = 0;
    if(log2(k) < n - 2){
        ans.push_back(1);
        memoize(n - 1, k, cntr + 1);
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (k < loss) {
            break;
        }
        best = i;
        ploss = loss;
        if(n - i - 1 >= 0) loss += powr[n - i - 1];
    }
    ans.push_back(best);
    memoize(n - 1, k - ploss, cntr + 1);
}
 
void solve() {
    long long n, k;
    cin >> n >> k;
    ans.clear();
    memoize(n, k - 1, 0);
    //cout << ans[0] << endl;
    int cur = 1;
    map<long long, long long> myMap;
    vector<long long> v;
    if(k > powr[n - 1]){
        cout << -1 << endl;
        return;
    }
    while(v.size() < ans.size()){
        long long prev = cur + ans[v.size()] - 1;
        v.push_back(prev);
        myMap[prev] = true;
        if(ans[v.size() - 1] > 1) {
            int j = 1;
            while (prev > j) {
                if (!myMap[prev - j]) {
                    v.push_back(prev - j);
                    j++;
                } else {
                    break;
                }
            }
            cur = prev + 1;
        }
        while (myMap[cur]) {
            cur++;
        }
    }
    for(long long i: v){
        cout << i << " ";
    }
    cout << endl;
}
 
int main() {
    powr.resize(100000);
    powr[0] = 1;
    for(int i = 1; i < 61; i++){
        powr[i] = powr[i - 1] * 2;
    }
    for(int i = 61; i < powr.size(); i++){
        powr[i] = LLONG_MAX;
    }
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
