    #include <iostream>
    #include <unordered_map>
    #include <algorithm>
    #include <vector>
    #include <cmath>
    #include <map>
    using namespace std;
    int largest2(int x){
      int counter = 1;
      while(x % 2 == 0){
        x /= 2;
        counter *= 2;
      }
      return counter;
    }
    struct tripl{
      int first;
      int second;
      int ind;
    };
    bool comp(tripl p1, tripl p2){
      if(p1.first == p2.first){
        return p1.second > p2.second;
      }
      return p1.first < p2.first;
    }
    void solve(){
      int n;
      cin >> n;
      tripl arr[n];
      map<pair<int,int>,int> ind;
      for(int i = 0; i < n; i++){
        cin >> arr[i].first >> arr[i].second;
        if(arr[i].first > arr[i].second){
          swap(arr[i].first, arr[i].second);
        }
        arr[i].ind = i;
      }
      sort(arr, arr + n, comp);
      int smallestY = pow(10,9);
      int bind = 0;
      int ans[n];
      for(int i = 0; i < n; i++){
        ans[i] = -2;
      }
      for(int i = 0; i < n; i++){
        if(arr[i].second > smallestY){
          ans[arr[i].ind] = bind;
        }else{
          bind = arr[i].ind;
          smallestY = arr[i].second;
        }
      }
      for(int i: ans){
        cout << i + 1 << " ";
      }
      cout << endl;
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
