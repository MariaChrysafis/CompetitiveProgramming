    #include <iostream>
    #include <vector>
    #include <algorithm>
    using namespace std;
    int r;
    struct matrix{
      long long a,b,c,d;
      matrix operator *(matrix mat){
        matrix ans;
        ans.a = a * mat.a + b * mat.c;
        ans.b = a * mat.b + b * mat.d;
        ans.c = c * mat.a + d * mat.c;
        ans.d = c * mat.b + d * mat.d;
        if(ans.a >= r) ans.a %= r;
        if(ans.b >= r) ans.b %= r;
        if(ans.c >= r) ans.c %= r;
        if(ans.d >= r) ans.d %= r;
        return ans;
      }
    };
    pair<int,int> merge(pair<int,int> p1, pair<int,int> p2){
      return make_pair(p1.first,p2.second);
    }
    int cl(int x){
      int pwr = 1;
      while(pwr < x){
        pwr *= 2;
      }
      return pwr;
    }
    matrix identity = {1,0,0,1};
    struct segmentTree{
      vector<matrix> v;
      vector<pair<int,int>> vec;
      vector<matrix> arr;
      matrix build(int ind){
        if(ind >= v.size() - 1){
          arr[ind] = v[ind - (v.size() - 1)];
          return arr[ind];
        }
        arr[ind] = build(2 * ind + 1) * build(2 * ind + 2);
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
      matrix interval(int i, int L, int R){
        if(vec[i].first > R || vec[i].second < L){
          return identity;
        }
        if(vec[i].first >= L && vec[i].second <= R){
          return arr[i];
        }
        matrix a = interval(2 * i + 1,L,R);
        matrix b = interval(2 * i + 2,L,R);
        return a * b;
      }
    };
    int main(){
      ios_base::sync_with_stdio(false);
      cin.tie(NULL);
      int n,m;
      cin >> r >> n >> m;
      vector<matrix> v1;
      for(int i = 0; i < n; i++){
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        v1.push_back({a,b,c,d});
      }
      int x = cl(n);
      for(int i = n; i < x; i++){
        v1.push_back(identity);
      }
      segmentTree segTree;
      vector<pair<int,int>> vec1;
      vec1.resize(2 * x);
      vector<matrix> arr1;
      arr1.resize(2 * x);
      segTree.v = v1;
      segTree.vec = vec1;
      segTree.arr = arr1;
      segTree.build(0);
      segTree.build2(0);
      while(m--){
        int L,R;
        cin >> L >> R;
        L--;
        R--;
        matrix prod = segTree.interval(0,L,R);
        cout << prod.a << " " << prod.b << '\n';
        cout << prod.c << " " << prod.d << '\n';
        cout << '\n';
      }
    }
