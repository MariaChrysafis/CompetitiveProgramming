#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
struct BIT{
    vector<long long> bit;
    void update_point(long long ind, long long val){
        ind++;
        while(ind < bit.size()){
            bit[ind] += val;
            ind += ind & (-ind);
        }
    }
    void update_range(int l, int r, long long x){
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
        bit.resize(v.size() + 2);
        for(int i = 0; i < bit.size(); i++){
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
    BIT b1, b2, b3;
    int n, q;
    cin >> n >> q;
    vector<long long> unit(n);
    vector<long long> orig(n);
    for(int i = 0; i < n; i++){
        unit[i] = 0;
        cin >> orig[i];
    }
    /*
     * b1 -> \sum (X - L)^2
     * b2 -> coefficient of i
     * b3 -> coefficient of i^2
     */
    b1.construct(unit);
    b2.construct(unit);
    b3.construct(unit);
    while(q--){
        int t;
        cin >> t;
        if(t == 1){
            long long l, r, x;
            cin >> l >> r >> x;
            l--, r--;
            b1.update_range(l, r, (x - l - 1) * (x - l - 1));
            b2.update_range(l, r, 2 * (x - l - 1));
            b3.update_range(l, r, 1);
        }else{
            long long y;
            cin >> y;
            y--;
            cout << b1.query(y) + b2.query(y) * (y + 1) + b3.query(y) * (y + 1) * (y + 1) + orig[y] << endl;
        }
    }

}
