class Solution {
public:
    int count_oc(string sub, string s){
        if(sub.length() == 0) return s.length();
        int ind = 0;
        int cntr = 0;
        for(int i = 0; i < s.length(); i++) {
            if(sub[ind] == s[i]){
                ind++;
                //cout << i << " " << ind << endl;
                if(ind == (int)sub.length()){
                    ind = 0;
                    cntr++;
                    //cout << "YES|n";
                }
            }
        }
        return cntr;
    }
    string best;
    void rec(string sub, string s, int k) {
        //cout << sub << endl;
        if(count_oc(sub, s) < k) {
            return;
        }
        if(sub.length() >= best.length() && sub > best) {
            best = sub;
        }
        for(char c = 'a'; c <= 'z'; c++){
            rec(sub + c, s, k);
        }
    }
    string longestSubsequenceRepeatedK(string s, int k) {
        //cout << count_oc("le", "letsleetcode");
        //return "";
        rec("", s, k);
        return best;
    }
};
