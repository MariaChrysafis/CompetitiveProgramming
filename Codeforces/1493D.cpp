#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <set>
#define ll long long
const int MOD = pow(10,9) + 7;
using namespace std;
vector<pair<int,int>> convert(vector<int> v){
    vector<pair<int,int>> ans;
    map<int,int> oc;
    map<int,bool> seen;
    for(int i: v){
        oc[i]++;
    }
    for(int i: v){
        if(seen[i]){
            continue;
        }
        seen[i] = true;
        ans.push_back({i, oc[i]});
    }
    return ans;
}
struct NT{
    int MAX;
    vector<int> isPrime;
    vector<int> primes;
    vector<int> pf;
    vector<int> ind;
    void init(){
        isPrime.resize(MAX);
        for(int i = 0; i < MAX; i++){
            isPrime[i] = -1;
        }
    }
    void Solve(){
        isPrime[0] = 0;
        isPrime[1] = 0;
        for(int i = 2; i < MAX; i++){
            if(isPrime[i] == -1){
                for(int j = 2 * i; j < MAX; j += i){
                    if(isPrime[j] == -1){
                        isPrime[j] = i; // the smallest prime factor of i
                    }
                }
            }
        }
    }
    void generate(){
        for(int i = 0; i < MAX; i++){
            if(isPrime[i] == -1){
                primes.push_back(i);
            }
        }
        ind.resize(MAX);
        for(int i = 0; i < primes.size(); i++){
            ind[primes[i]] = i;
        }
    }
    int factorize(int x){
        if(isPrime[x] == 0){
            return 0;
        }
        if(isPrime[x] == -1){
            pf.push_back(x);
            return x;
        }
        pf.push_back(isPrime[x]);
        return factorize(x/isPrime[x]);
    }
    vector<int> prime_factorize(int x){
        pf.clear();
        factorize(x);
        return pf;
    }
};
vector<int> glob;
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
    v[k] = u;
    while(ind != 0){
      int parent = (ind - 1)/2;
      arr[parent] = min(arr[parent * 2 + 1],arr[parent * 2 + 2]);
      ind = parent;
    }
  }
};
int fact(int n, int p){
    int pwr = p;
    int cntr = 0;
    while(n % pwr == 0){
        pwr *= p;
        cntr++;
    }
    return cntr;
}
struct que{
    int first;
    int second;
    int ind;
};
NT nt;
vector<pair<int,int>> q;
vector<vector<que>> queries;
vector<ll> GCD;
vector<int> oc;
void solve(int p){
    if(oc[p] + queries[p].size() < glob.size()){
 
        return;
    }
    //first construct the segment tree
    vector<int> crux;
    int x = cl(glob.size());
    crux.resize(x);
    vector<int> arr(2 * x);
    vector<pair<int,int>> vec1(2 * x);
    for(int i = 0; i < glob.size(); i++){
        crux[i] = fact(glob[i], p);
    }
    segmentTree st;
    st.v = crux, st.arr = arr, st.vec = vec1, st.build(0), st.build2(0), st.INF = pow(10,8);
    vector<que> vec = queries[p];
    int prev = st.interval(0, 0, glob.size() - 1);
    for(auto pr: vec){
        int x = pr.first;
        int y = pr.second;
        //int l1 = st.interval(0, 0, glob.size() - 1);
        st.update(x - 1,st.v[x - 1] + y);
        int l2 = st.interval(0, 0, glob.size() - 1);
        int dl = l2 - prev;
        prev = l2;
        GCD[pr.ind] *= pow(p, dl);
        //if(GCD[pr.ind] > MOD) GCD[pr.ind] %= MOD;
    }
 
}
 
void process(int a, int b, int ind){
    //we're essentially replacing a with b
    vector<pair<int,int>> v1 = convert(nt.prime_factorize(b));
    for(pair<int,int> p: v1){
        int x = p.first;
        que qq;
        qq.first = a, qq.second = p.second, qq.ind = ind;
        queries[x].push_back(qq);
    }
}
int GCD__(int x, int y){
    if(min(x,y) == 0){
        return max(x,y);
    }
    return GCD__(max(x,y) % min(x, y), min(x,y));
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, qu;
    cin >> n >> qu;
    oc.resize(2 * pow(10,5));
    int strt;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        glob.push_back(a);
    }
    nt.MAX = 2 * pow(10, 5) + 1, nt.init(), nt.Solve(), nt.generate();
    //vector<int> v = nt.prime_factorize(18);
    //vector<pair<int,int>> v1 = convert(v);
    queries.resize(nt.ind.size());
    for(int i = 0; i < qu; i++){
        int a, b;
        cin >> a >> b;
        process(a, b, i);
        q.push_back({a,b});
    }
    GCD.resize(qu);
    for(int i = 0; i < qu; i++){
        GCD[i] = 1;
    }
    strt = glob[0];
    for(int i = 0; i < n; i++){
        vector<pair<int,int>> pf = convert(nt.prime_factorize(glob[i]));
        for(auto pr: pf){
            oc[pr.first]++;
        }
        strt = GCD__(strt,glob[i]);
    }
    for(int i: nt.primes){
        solve(i);
    }
 
    GCD[0] *= strt;
    cout << GCD[0] << endl;
    for(int i = 1; i < qu; i++){
        GCD[i] *= GCD[i - 1];
        if(GCD[i] > MOD) GCD[i] %= MOD;
        cout << GCD[i] << endl;
    }
    //vector<pair<int,int>> v = convert(nt.prime_factorize(30030));
}
