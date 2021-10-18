class Solution {
public:
    bool areNumbersAscending(string s) {
        int cur = 0;
        vector<int> v;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] < '0' || s[i] > '9') {
                if (cur != 0) {
                    v.push_back(cur);
                }
                cur = 0;
                continue;
            }
            cur = 10 * cur + (s[i] - '0');
        }
        if (cur != 0) {
            v.push_back(cur);
        }
        for (int i = 0; i < v.size() - 1; i++) {
            if (v[i] >= v[i + 1]) {
                return false;
            }
        }
        return true;
    }
};
