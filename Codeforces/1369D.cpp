#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
 
using namespace std;
const int MAX = 2e6 + 7;
const int MOD = 1e9 + 7;
int main() {
    vector<long long> ans(MAX);
    ans[0] = 0;
    ans[1] = 0;
    ans[2] = 0;
    ans[3] = 1;
    ans[4] = 1;
    ans[5] = 12;
    for(int i = 5; i < MAX; i++){
        if(i % 3 == 2){
            ans[i] = (ans[i - 2] * 2 + ans[i - 1]) % MOD;
        }else{
            ans[i] = (ans[i - 4] * 4 + ans[i - 3] * 4 + ans[i - 2] + 1) % MOD;
        }
    }
    int t;
    cin >> t;
    while(t--){
        int x;
        cin >> x;
        cout << (ans[x] * 4) % MOD << endl;
    }
}
