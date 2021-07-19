class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters) {
        text += " ";
        vector<string> words;
        string cur;
        map<char,bool> broken;
        for(char c = 'a'; c <= 'z'; c++) broken[c] = false;
        for(char c: brokenLetters) broken[c] = true;
        for(int i = 0; i < text.size(); i++){
            if(text[i] == ' '){
                words.push_back(cur);
                cur = "";
            }else{
                cur += text[i];
            }
        }
        int ans = 0;
        for(string s: words){
            bool fine = true;
            for(char c: s){
                if(broken[c]){
                    fine = false;
                }
            }
            ans += fine;
        }
        //cout << endl;
        return ans;
    }
};
