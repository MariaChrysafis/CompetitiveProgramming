#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#include <array>
#include <iomanip>
 
#define ll long long
#define endl '\n'
 
using namespace std;
void print(vector<int> v){
    for(int i : v) cout << i << " ";
    cout << endl;
}
void print(vector<ll> v){
    for(ll i : v) cout << i << " ";
    cout << endl;
}
void print(vector<vector<int>> v){
    for(vector<int> vec: v) print(vec);
    cout << endl;
}
void print(vector<vector<ll>> v){
    for(vector<ll> vec: v) print(vec);
    cout << endl;
}
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
        arr[ind] = min(build(2 * ind + 1),build(2 * ind + 2));
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
        return min(a,b);
    }
    void update(int k, int u){
        int ind = (v.size() - 1) + k;
        arr[ind] = u;
        while(ind != 0){
            int parent = (ind - 1)/2;
            arr[parent] = min(arr[parent * 2 + 1],arr[parent * 2 + 2]);
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
    st.INF = 1e9;
    return st;
}
int n, m;
vector<int> a, b;
segmentTree st;
int firstOc(int left, int right, int x, int end){
    if(left == right){
        return left;
    }
    int mid = (left + right)/2;
    int ans = st.interval(0, mid, end);
    if(ans > x){
        return firstOc(left, mid - 1, x, end);
    }else if(ans == x){
        return firstOc(left, mid, x, end);
    }else{
        return firstOc(mid + 1, right, x, end);
    }
}
int main() {
    cin >> n >> m;
    a.resize(n), b.resize(m);
    map<int,int> oc;
    for(int i = 0; i < n; i++) cin >> a[i], oc[a[i]] = i + 1;
    for(int i = 0; i < m; i++) cin >> b[i];
    st = generate(a);
    vector<int> v(m);
    for(int i = 0; i < n; i++){
        if(a[i] < b[0]){
            cout << 0;
            return 0;
        }
    }
    for(int i = oc[b[m - 1]]; i < n; i++){
        if(a[i] < b[m - 1]){
            cout << 0;
            return 0;
        }
    }
    for(int i = 0; i < m; i++){
        if(oc[b[i]] == 0){
            cout << 0 << endl;
            return 0;
        }
    }
    vector<int> marked(n);
    for(int i = 0; i < n; i++){
        marked[i] = 0;
    }
    for(int i = 0; i < m; i++){
        marked[oc[b[i]] - 1] = i + 1;
    }
    int curMax = 0;
    for(int i = 0; i < n; i++){
        if(a[i] < curMax){
            cout << 0 << endl;
            return 0;
        }
        if(marked[i]){
            curMax = b[marked[i] - 1];
            //cout << curMax << " ";
        }
    }
    //return 1;
    ll ans = 1;
    for(int i = m - 1; i >= 1; i--){
        v[i] = firstOc(0, n - 1, b[i], oc[b[i]] - 1);
        //cout << oc[b[i]] << " " << v[i] << endl;
        ans *= (oc[b[i]] - v[i]);
        if(i != m - 1 && oc[b[i]] > oc[b[i + 1]]){
            cout << 0;
            return 0;
        }
        ans %= 998244353;
    }
    cout << ans << endl;
}
