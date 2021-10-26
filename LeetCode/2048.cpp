class Solution {
public:
    bool balanced (string s) {
        int oc[10];
        for (int i = 0; i < 10; i++) oc[i] = 0;
        for (int i = 0; i < s.length(); i++) {
            oc[s[i] - '0']++;
        }
        for (int c = 0; c <= 9; c++) {
            if (oc[c] == 0) continue;
            if (oc[c] != c) {
                return false;
            }
        }
        return true;
    }
    int nextBeautifulNumber(int n) {
        for (int i = n + 1; i < (int)1e9; i++) {
            string s = to_string(i);
            if (balanced(s)) {
                return i;
            }
        }
        return -1;
    }
};
