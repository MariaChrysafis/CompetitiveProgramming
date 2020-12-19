class Solution {
public:
    string rev(string s){
        string str;
        for(int i = s.length() - 1; i >= 0; i--){
            str += s[i];
        }
        return str;
    }
    int reverse(long long x) {
        bool neg = (x < 0);
        string s = to_string(x);
        s = rev(s);
        long long x1 = stoll(s);
        if(x1 > INT_MAX) return 0;
        return pow(-1,neg) * stoi(s);
    }
};
