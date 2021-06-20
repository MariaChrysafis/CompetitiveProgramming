class Solution {
public:
    bool isOdd(char c){
        return (c == '1' || c == '3' || c == '5' || c == '7' || c == '9');
    }
    string largestOddNumber(string num) {
        int ind = -1;
        for(int i = num.length() - 1; i >= 0; i--){
            if(isOdd(num[i])){
                ind = i;
                break;
            }
        }
        string str = "";
        for(int i = 0; i <= ind; i++){
            str += num[i];
        }
        return str;
    }
};
