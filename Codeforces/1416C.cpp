#include <iostream>
#include <vector>
using namespace std;
 
struct solve{
    vector<vector<long long>> dp;
    void rec(vector<long long> v, long long depth){
        if(depth < 0 || v.size() == 0) return;
        long long cnt[2];
        cnt[0] = cnt[1] = 0;
        vector<long long> p[2];
        for(long long x: v){
            bool b = x & (1ll << depth);
            if(!b) dp[depth][0] += cnt[1]; //10 inversions
            else dp[depth][1] += cnt[0]; //01 inversions
            cnt[b]++;
            p[b].push_back(x);
        }
        rec(p[0], depth - 1);
        rec(p[1], depth - 1);
    }
    void read(){
        int n;
        cin >> n;
        vector<long long> arr(n);
        for(int i = 0; i < n; i++) cin >> arr[i];
        dp.resize(34);
        for(int i = 0; i < dp.size(); i++){
            dp[i].resize(2);
        }
        rec(arr, 30);
        long long ans = 0;
        long long val = 0;
        for(int i = 0; i < 30; i++){
            long long cnt0 = dp[i][0];
            long long cnt1 = dp[i][1];
            if(cnt0 == cnt1 && cnt0 == 0) continue;
            ans += min(cnt0, cnt1);
            if(cnt1 < cnt0) val += (1 << i);
        }
        cout << ans << " " << val << '\n';
    }
};
int main(){
    solve s;
    s.read();
}
