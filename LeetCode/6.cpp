class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows == 1){
            return s;
        }
        vector<vector<int>> v;
        v.resize(numRows);
        for(int i = 0; i < numRows; i++){
            v[i].push_back(i);
        }
        int j = numRows;
        string str = "";
        while(j < s.length()){
            for(int i = numRows - 2; i >= 0; i--){ 
                v[i].push_back(j);
                j++;
            } 
            v[numRows - 1].push_back(-1);
            for(int i = 1; i < numRows; i++){
                v[i].push_back(j);
                j++;
            }
            v[0].push_back(-1);
        }
        for(int i = 0; i < numRows; i++){
            for(int j: v[i]){
                if(j >= s.length() || j == -1) continue;
                str = str + s[j];
            }   
        }
        return str;
    }
};
