class Solution {
public:
    int gcd(int a, int b){
        if(min(a,b) == 0) return max(a,b);
        return gcd(max(a,b) % min(a,b), min(a,b));
    }
    const int MOD = 1e9 + 7;
    long long mult(long long x, long long y){
        return (x * y) % MOD;
    }
    map<int,int> oc;
    vector<int> v;
    int cntr = 0;
    void rec(string s, int len){
        for(int i = 0; i < s.length(); i++){
            for(int j = i + 1; j < s.length(); j++){
                if(s[i] == '1' && s[j] == '1' && (gcd(v[i], v[j]) != 1)){
                    return;
                }
            }
        }
        if(s.length() == len){
            long long delta = 1;
            for(int i = 0; i < s.length(); i++){
                if(s[i] == '1'){
                    delta = mult(delta, oc[v[i]]);
                }
            }
            cntr += delta;
            cntr %= MOD;
            return;
        }
        rec(s + '1', len);
        rec(s + '0', len);
    }
    long long binpow(long long a, long long b){
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
    int numberOfGoodSubsets(vector<int>& nums) {
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] % 4 == 0 || nums[i] % 9 == 0 || nums[i] % 25 == 0 || nums[i] == 1) continue;
            oc[nums[i]]++;
        }
        for(pair<int,int> p: oc){
            //if(p.first == 1) continue;
            v.push_back(p.first);
            //cout << v.back() << endl;
        }
        for(int i: nums) oc[1] += (i == 1);
        rec("", v.size());
        return mult(cntr - 1, binpow(2, oc[1]));
    }
};
