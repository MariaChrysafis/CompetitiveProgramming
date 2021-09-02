class Solution {
public:
    bool valid(string key, string pos){
        for (int i = 0; i < key.size(); i++){
            if (key[i] == pos[i]){
                return false;
            }
        }
        return true;
        
    }
    vector<string> pos;
    void rec(string s, int des){
        if(s.length() == des){
            for(int i = 0; i < s.length() - 1; i++){
                if(s[i] == s[i + 1]){
                    return;
                }
            }
            pos.push_back(s);
            return;
        }
        rec(s + '0', des);
        rec(s + '1', des);
        rec(s + '2', des);
    }
    const int MOD = 1e9 + 7;
    int colorTheGrid(int m, int n) {
        rec("", m);
        map<string, int> prev;
        map<string, int> cur;
        for(string key: pos){
            prev[key] = 1;
        }                          
        long long ans = 0;                            
        for(int i = 1; i < n; i++){
            for(string key: pos){
                int ans = 0;
                for(string pl: pos){
                    if(valid(key, pl)){
                        ans += prev[pl];
                        if(ans >= MOD) ans -= MOD;
                    }
                }
                cur[key] = ans;
            }
            prev = cur;
        }
        for(string s: pos){
            ans += prev[s];
            if(ans >= MOD) ans -= MOD;
        }
        return ans;
    }
};
