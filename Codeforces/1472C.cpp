    #include <iostream>
    #include <unordered_map>
    #include <vector>
    using namespace std;
    int largest2(int x){
      int counter = 1;
      while(x % 2 == 0){
        x /= 2;
        counter *= 2;
      }
      return counter;
    }
    long long solve(){
      int n;
      cin >> n;
      int arr[n];
      bool mark[n];
      int dp[n];
      for(int i = 0; i < n; i++){
        cin >> arr[i];
        mark[i] = false;
        dp[i] = -1;
      }
      long long myMax = 0;
      for(int i = 0; i < n; i++){
        if(dp[i] != -1){
          continue;
        }
        int nxt = i;
        vector<int> path;
        while(true){
          if(nxt >= n){
            break;
          }
          if(dp[nxt] != -1){
            break;
          }
          path.push_back(nxt);
          nxt = arr[nxt] + nxt;
        }
        int counter = 0;
        for(int j: path){
          counter += arr[j];
        }
        if(counter > myMax){
          myMax = counter;
        }
        counter = arr[i];
        for(int j = 0; j < path.size(); j++){
          dp[path[j]] = counter;
          counter -= arr[path[j]];
        }
      }
      return myMax;
    }
    int main(){
      ios_base::sync_with_stdio(false);
      cin.tie(NULL);
      int t;
      cin >> t;
      while(t--){
        int b = solve();
        cout << b << '\n';
      }
    }
