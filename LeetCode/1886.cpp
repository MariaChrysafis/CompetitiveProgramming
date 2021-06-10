class Solution {
public:
    void print(vector<vector<int>> v){
        for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < v[i].size(); j++){
                cout << v[i][j] << " ";
            }
            cout << endl;
        }
    }
    vector<vector<int>> rotate(vector<vector<int>> v){
        int n = v.size();
        for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < i; j++){
                swap(v[i][j], v[j][i]);
            }
        }
        for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < v[i].size()/2; j++){
                swap(v[i][j], v[i][n - 1 - j]);
            }
        }
        return v;
    }
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        if(mat == target) return true;
        if(rotate(mat) == target) return true;
        if(rotate(rotate(mat)) == target) return true;
        if(rotate(rotate(rotate(mat))) == target) return true;
        return false;
    }
};
