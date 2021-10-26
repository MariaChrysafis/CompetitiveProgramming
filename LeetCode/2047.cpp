class Solution {
public:
    bool valid (string s){
        map<char,int> cnt;
        for (int i = 0; i < s.length(); i++) {
            char c = s[i];
            if (c < 'a' || c > 'z') {
                if (c == '-') {
                    if (i == 0 || i == s.length() - 1) return false;
                    if ((s[i - 1] < 'a' || s[i - 1] > 'z') || (s[i + 1] < 'a' || s[i + 1] > 'z')) return false;
                }
                if (c == '!' && i != s.length() - 1) return false;
                if (c == ',' && i != s.length() - 1) return false;
                if (c == '.' && i != s.length() - 1) return false;
                if (c != '-' && c != '!' && c != ',' && c != '.') return false;
            }
            cnt[c]++;
        }
        if (cnt['-'] >= 2 || cnt['?'] >= 2 || cnt['.'] >= 2 || cnt[','] >= 2) return false;
        return true;
    }
    int countValidWords(string sentence) {
        vector<string> words;
        string cur = "";
        for (int i = 0; i < sentence.size(); i++) {
            if (sentence[i] == ' ') {
                if (cur != "") words.push_back(cur);
                cur = "";
            } else {
                cur += sentence[i];
            }
        }
        if (cur != "") {
            words.push_back(cur);
        }
        int cntr = 0;
        for (string s: words) {
            //cout << s << endl;
            if (valid(s)) {
                //cout << s << endl;
                cntr++;
            }
        }
        return cntr;
    }
};
