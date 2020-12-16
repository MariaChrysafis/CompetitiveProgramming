class Solution {
public:
    int asci(char c){
        return int(c);
    }
    int lengthOfLongestSubstring(string s) {
        if(s.length() == 0 || s.length() == 1){
            return s.length();
        }
        int lastOc[127];
        for(int i = 0; i < 127; i++){
            lastOc[i] = -1;
        }
        lastOc[asci(s[s.length() - 1])] = s.length() - 1;
        int myMax = 0;
        int prev,cur;
        cur = 1;
        prev = -1;
        for(int i = s.length() - 2; i >= 0; i--){
            swap(cur,prev);
            int c = asci(s[i]);
            if(lastOc[c] - i <= prev && lastOc[c] != -1){
                cur = lastOc[c] - i;
            }else{
                cur = prev + 1;
            }
            lastOc[c] = i;
            if(myMax < cur){
                myMax = cur;
            }
        }
        return myMax;
    }
};
