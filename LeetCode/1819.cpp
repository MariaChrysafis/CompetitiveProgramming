class Solution {
public:
    set<int> nums_copy;
    vector<bool> isValid;
    int gcd(int a, int b){
        if(min(a,b) == 0) return max(a,b);
        return gcd(max(a,b) % min(a,b), min(a,b));
    }
    bool valid(int x){
        int g = 0;
        for(int i = 0; i <= 2e5; i += x){
            if(isValid[i]){
                g = gcd(g, i/x);
                if(g == 1) return true;
            }
        }
        return (g == 1);
    }
    int countDifferentSubsequenceGCDs(vector<int>& nums) {
        isValid.resize((int)2e5 + 1);
        for(int i: nums) {
            //nums_copy.insert(i);
            isValid[i] = true;
        }
        int cntr = 0;
        for(int i = 1; i <= 2e5; i++){
            if(valid(i)){
                cntr++;
            }
        }
        return cntr;
    }
};
