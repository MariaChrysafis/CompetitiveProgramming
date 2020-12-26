class Solution {
public:
    string maximumBinaryString(string binary) {
        int ind = -1;
        int preones = 0;
        for(int i = 0; i < binary.length(); i++){
            if(binary[i] == '0'){
                ind = i;
                break;
            }
        }
        if(ind == -1){
            return binary;
        }
        preones = ind;
        string s = "";
        for(int i = 0; i < preones; i++){
            s += '1';
        }
        int zeroes = 0;
        for(int i = ind; i < binary.length(); i++){
            if(binary[i] == '0'){
                zeroes++;
            }
        }
        for(int i = 0; i < zeroes - 1; i++){
            s += '1';
        }
        s += '0';
        while(s.length() < binary.length()){
            s += '1';
        }
        return s;
        
    }
};
