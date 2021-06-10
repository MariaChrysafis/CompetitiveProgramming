class Solution {
public:
    void print(vector<int> v){
        for(int i: v){
            cout << i << " ";
        }
        cout << endl;
    }
    int sum(vector<int> v){
        int sm = 0;
        for(int i: v) sm += i;
        return sm;
    }
    vector<int> remap(vector<int> v){
        set<int> s;
        for(int i: v){
            s.insert(i);
        }
        map<int,int> oc;
        int x = 0;
        for(auto it = s.begin(); it != s.end(); it++){
            oc[*it] = x++;
        }
        vector<int> vec;
        for(int i = 0; i < v.size(); i++){
            vec.push_back(oc[v[i]]);
        }
        return vec;
    }
    int reductionOperations(vector<int>& nums) {
        return sum(remap(nums));
    }
};
