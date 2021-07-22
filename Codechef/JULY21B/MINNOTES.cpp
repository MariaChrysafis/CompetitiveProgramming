#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;
int cl(int x){
    int pwr = 1;
    while(pwr < x){
        pwr *= 2;
    }
    return pwr;
}
pair<int,int> merge(pair<int,int> p1, pair<int,int> p2){
    return make_pair(p1.first,p2.second);
}
int gcd(int a, int b){
    if(min(a,b) == 0) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}
struct segmentTree{
    vector<pair<int,int>> vec;
    vector<int> v;
    vector<int> arr;
    int INF;
    int build(int ind){
        if(ind >= v.size() - 1){
            arr[ind] = v[ind - (v.size() - 1)];
            return arr[ind];
        }
        arr[ind] = gcd(build(2 * ind + 1),build(2 * ind + 2));
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
    int interval(int i, int L, int R){
        if(vec[i].first > R || vec[i].second < L){
            return INF;
        }
        if(vec[i].first >= L && vec[i].second <= R){
            return arr[i];
        }
        int a = interval(2 * i + 1,L,R);
        int b = interval(2 * i + 2,L,R);
        return gcd(a,b);
    }
    void update(int k, int u){
        int ind = (v.size() - 1) + k;
        arr[ind] = u;
        while(ind != 0){
            int parent = (ind - 1)/2;
            arr[parent] = gcd(arr[parent * 2 + 1],arr[parent * 2 + 2]);
            ind = parent;
        }
    }
};
segmentTree generate(vector<int> v){
    segmentTree st;
    st.v = v;
    vector<int> arr(2 * cl(v.size()));
    vector<pair<int,int>> vec(2 * cl(v.size()));
    st.arr = arr, st.vec = vec;
    vector<int> v1;
    v1.resize(cl(v.size()));
    for(int i = 0; i < v.size(); i++){
        v1[i] = v[i];
    }
    st.v = v1;
    st.build(0);
    st.build2(0);
    st.INF = 0;
    return st;
}
void solve(){
    int n;
    cin >> n;
    vector<int> v(n);
    vector<int> pos;
    long long sum = 0;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        sum += v[i];
    }
    if(n == 1){
        cout << 1 << endl;
        return;
    }
    sort(v.begin(), v.end());
    segmentTree st = generate(v);
    st.build(0), st.build2(0);
    long long myMin = sum/st.interval(0, 0, n - 1);
    for(int i = 0; i < v.size(); i++){
        int left = 0;
        if(i != 0) left = st.interval(0, 0, i - 1);
        int right = 0;
        if(i != v.size()) right = st.interval(0, i + 1, n - 1);
        int x = gcd(left, right);
        myMin = min(myMin, (sum - v[i])/x + 1);
    }
    cout << myMin << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
