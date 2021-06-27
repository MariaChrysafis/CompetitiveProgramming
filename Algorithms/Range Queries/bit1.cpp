#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
struct BIT{
    vector<long long> bit; //1-indexed
    void update_point(long long ind, long long val){
        ind++;
        while(ind < bit.size()){
            bit[ind] += val;
            ind += ind & (-ind);
        }
    }
    void update_range(int l, int r, int x){
        update_point(l, x);
        update_point(r + 1, -x);
    }
    long long query(int b){
        b++;
        long long sum = 0;
        for(; b ; b -= b & (-b)) sum += bit[b];
        return sum;
    }
    void construct(vector<long long> v){
        bit.resize(v.size() + 1);
        for(int i = 0; i <= v.size(); i++){
            bit[i] = 0;
        }
        for(int i = 0; i < v.size(); i++) {
            update_point(i, v[i]);
        }
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    BIT b;
    int n, m;
    cin >> n >> m;
    vector<long long> v(n);
    for(int i = 0; i < n; i++){
        v[i] = 0;
    }
    b.construct(v);
    while(m--){
        int t;
        cin >> t;
        if(t == 1){
            int l, r, x;
            cin >> l >> r >> x;
            b.update_range(l, r - 1, x);
        }else{
            int dum;
            cin >> dum;
            //for(int i = 0; i < n; i++) cout << b.query(i) << " ";
            cout << b.query(dum) << endl;
        }
    }
 
}
