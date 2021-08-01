class Solution {
public:
    vector<long long> pref;
    const int MAX = 1e5;
    long long binSearch(long long l, long long r, long long des){
        long long m = (l + r)/2;
        if(l == r){
            return l;
        }
        if(pref[m] >= des){
            return binSearch(l, m, des);
        }else{
            return binSearch(m + 1, r, des);
        }
    }
    void print(){
        for(long long i: pref) cout << i << " ";
        cout << endl;
    }
    long long minimumPerimeter(long long neededApples) {
        pref.push_back(0);
        while(pref.size() != MAX){
            long long sz = pref.size();
            long long delta = (sz * 2 + 2) * (sz * 2 + 2) - 4 + 8 * (sz) * (sz - 1);
            pref.push_back(pref.back() + delta);
        }
        //print();
        return binSearch(0, pref.size() - 1, neededApples) * 8;
    }
};
