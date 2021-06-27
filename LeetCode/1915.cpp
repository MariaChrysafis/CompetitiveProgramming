class Solution {
public:
    vector<int> v;
    int to_int(char c){
        return c - 'a';
    }
    int dif(long long a, long long b){
        int cntr = 0;
        for(int i = 0; i < 11; i++){
            int x = (a & (1 << i));
            int y = (b & (1 << i));
            if(x != y){
                cntr++;
            }
        }
        return cntr;
    }
    long long wonderfulSubstrings(string word) {
        vector<int> pref(word.length() + 1);
        for(int i = 0; i < pref.size(); i++){
            pref[i] = 0;
        }
        for(int i = 1; i < pref.size(); i++){
            pref[i] = pref[i - 1];
            int cur = to_int(word[i - 1]);
            if(pref[i] & (1 << cur)){
                pref[i] -= (1 << cur);
            }else{
                pref[i] += (1 << cur);
            }
        }
        map<long long, long long> oc;
        for(int i = 0; i < pref.size(); i++){
            oc[pref[i]]++;
        }
        long long cntr = 0;
        for(pair<long long,long long> v: oc){
            for(pair<long long, long long> v1: oc){
                if(v.first == v1.first){
                    cntr += v.second * (v.second - 1);
                }
                if(dif(v1.first,v.first) == 1){
                    cntr += v.second * v1.second;
                }
            }
        }
        cntr /= 2;
        return cntr;
    }
};
