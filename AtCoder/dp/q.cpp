#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
vector<long long> h, a;
vector<long long> dp, strict, unmap;
int n;
int cl(int x){
    int pwr = 1;
    while(pwr < x){
        pwr *= 2;
    }
    return pwr;
}
pair<long long,long long> merge(pair<long long,long long> p1, pair<long long,long long> p2){
    return make_pair(p1.first,p2.second);
}
struct segmentTree{
    vector<pair<long long,long long>> vec;
    vector<long long> v;
    vector<long long> arr;
    long long INF;
    int build(int ind){
        if(ind >= v.size() - 1){
            arr[ind] = v[ind - (v.size() - 1)];
            return arr[ind];
        }
        arr[ind] = max(build(2 * ind + 1),build(2 * ind + 2));
        return arr[ind];
    }
    pair<int,int> build2(int ind){
        if(ind >= v.size() - 1){
            int x = ind - (v.size() - 1);
            vec[ind] = make_pair(x,x);
            return vec[ind];
        }
        vec[ind] = merge(build2(2 * ind + 1),build2(2 * ind + 2));
        return vec[ind];
    }
    long long interval(int i, int L, int R){
        if(vec[i].first > R || vec[i].second < L){
            return INF;
        }
        if(vec[i].first >= L && vec[i].second <= R){
            return arr[i];
        }
        long long a = interval(2 * i + 1,L,R);
        long long b = interval(2 * i + 2,L,R);
        return max(a,b);
    }
    void update(int k, long long u){
        int ind = (v.size() - 1) + k;
        arr[ind] = u;
        while(ind != 0){
            int parent = (ind - 1)/2;
            arr[parent] = max(arr[parent * 2 + 1],arr[parent * 2 + 2]);
            ind = parent;
        }
    }
    void fill(vector<long long> inp){
        vector<long long> v1(cl(inp.size()));
        vector<long long> arr1(2 * cl(inp.size()));
        vector<pair<long long,long long>> vec1(2 * cl(inp.size()));
        for(int i = 0; i < v.size(); i++) v1[i] = inp[i];
        v = v1;
        arr = arr1;
        vec = vec1;
        INF = -pow(10,12);
        build(0);
        build2(0);
    }
};
vector<long long> uniform(int sz, long long ele){
    vector<long long> v;
    v.resize(sz);
    for(int i = 0; i < sz; i++){
        v[i] = ele;
    }
    return v;
}
int main(){
    cin >> n;
    h.resize(n), a.resize(n), dp.resize(n), unmap.resize(n), strict.resize(n);
    for(int i = 0; i < n; i++){
        cin >> h[i];
        h[i]--;
        unmap[h[i]] = i;
        dp[i] = -1;
    }
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    segmentTree strct;
    strct.fill(uniform(n, 0));
    dp[0] = a[0];
    strict[0] = a[0];
    strct.update(h[0], a[0]);
    for(int i = 1; i < n; i++){
        dp[i] = max(dp[i - 1], a[i]);
        strict[i] = a[i];
        long long s1 = strct.interval(0, 0, h[i]);
        //int d1 = DP.interval(0, 0, h[i]);
        dp[i] = max(dp[i], s1 + a[i]);
        strict[i] = max(s1 + a[i], strict[i]);
        strct.update(h[i],strict[i]);
    }
    cout << dp[n - 1] << endl;
}
