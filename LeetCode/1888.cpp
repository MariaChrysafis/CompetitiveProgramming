/*
111000
101010
*/

class Solution {
public:
    int to_int(char c){
        if(c == '0') return 0;
        else return 1;
    }
    int minFlips(string s) {
        int n = (int)s.length();
        int one_start[n];
        int zero_start[n];
        one_start[0] = (s[0] == '1');
        zero_start[0] = (s[0] == '0');
        for(int i = 1; i < n; i++){
            int val = to_int(s[i]);
            one_start[i] = one_start[i - 1] + (val != (i % 2));
            zero_start[i] = zero_start[i - 1] + (val == (i % 2));
        }
        if((int)s.length() % 2 == 0){
            return min(one_start[n - 1], zero_start[n - 1]);
        }
        int ans = min(one_start[n - 1], zero_start[n - 1]);
        for(int i = 0; i < n; i++){
            ans = min(ans, one_start[n - 1] - one_start[i] + zero_start[i]);
            ans = min(ans, zero_start[n - 1] - zero_start[i] + one_start[i]);
        }
        return ans;
    }
};
