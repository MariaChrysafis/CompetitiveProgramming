class Solution {
public:
    bool areOccurrencesEqual(string s) {
        map<char,int> oc;
        for(char c: s) oc[c]++;
        for(pair<char,int> p: oc){
            if(p.second != oc[s[0]]){
                return false;
            }
        }
        return true;
    }
};
