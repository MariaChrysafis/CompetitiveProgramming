class Solution {
public:
    int gcd(int a, int b){
        if(min(a,b) == 0) return max(a,b);
        return gcd(max(a,b) % min(a,b), min(a,b));
    }
    bool isGoodArray(vector<int>& nums) {
        int g = 0;
        for(int i: nums){
            g = gcd(g, i);
        }
        return (g == 1);
    }
};
