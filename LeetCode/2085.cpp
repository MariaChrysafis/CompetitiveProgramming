class Solution {
public:
    int countWords(vector<string>& words1, vector<string>& words2) {
        map<string,int> oc1, oc2;
        for (string s: words1) {
            oc1[s]++;
        }
        for (string s: words2) {
            oc2[s]++;
        }
        int ans = 0;
        for (auto& p: oc1) {
            if (p.second == 1 && oc2[p.first] == 1) {
                ans++;
            }
        }
        return ans;
    }
};
