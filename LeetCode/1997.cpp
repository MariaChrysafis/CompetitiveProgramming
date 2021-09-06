class Solution {
public:
    int firstDayBeenInAllRooms(vector<int>& nextVisit) {
        vector<long long> v;
        long long len = 0;
        for(int i = 0; i < nextVisit.size() - 1; i++){
            if(nextVisit[i] == i) {
                len += 2;
            } else {
                if(nextVisit[i] == 0){
                    len++, len *= 2;
                }else{
                    len += len - v[nextVisit[i] - 1];
                    len += 2;
                }
            }
            len += ((int)1e9 + 7);
            len %= ((int)1e9 + 7);
            v.push_back(len);
        }
        cout << endl;
        return len;
    }
};
