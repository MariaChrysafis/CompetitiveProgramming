#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
struct BIT{
    vector<long long> bit; //1-indexed
    long long pref(long long ind){
        long long ans = 0;
        ind++;
        while(ind > 0){
            //cout << ind << " ";
            ans += bit[ind];
            ind -= (ind & (-ind));
        }
        return ans;
    }
    long long sum(long long l, long long r){
        if(l == 0){
            return pref(r);
        }
        return pref(r) - pref(l - 1);
    }
    void update(long long ind, long long val){
        ind++;
        while(ind < bit.size()){
            bit[ind] += val;
            ind += ind & (-ind);
        }
    }
    void construct(vector<long long> v){
        bit.resize(v.size() + 1);
        for(int i = 0; i <= v.size(); i++){
            bit[i] = 0;
        }
        for(int i = 0; i < v.size(); i++) {
            update(i, v[i]);
        }
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    BIT b;
    int n, m;
    cin >> n >> m;
    vector<long long> v;
    for(int i = 0; i < n; i++){
        long long x;
        cin >> x;
        v.push_back(x);
    }
    b.construct(v);
    while(m--){
        long long t;
        cin >> t;
        if(t == 1){
            long long i, x;
            cin >> i >> x;
            b.update(i, x - v[i]);
            v[i] = x;
        }else{
            long long l, r;
            cin >> l >> r;
            cout << b.sum(l, r - 1) << endl;
        }
    }
 
}
