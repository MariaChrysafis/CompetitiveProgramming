    #include <iostream>
    using namespace std;
    int largest2(int x){
      int counter = 1;
      while(x % 2 == 0){
        x /= 2;
        counter *= 2;
      }
      return counter;
    }
    bool solve(){
      int n;
      cin >> n;
      int arr[n];
      long long sum = 0;
      for(int i = 0; i < n; i++){
        cin >> arr[i];
        sum += arr[i];
      }
      if(sum % 2 == 1){
        return false;
      }
      int pref[n];
      pref[0] = arr[0];
      for(int i = 1; i < n; i++){
        pref[i] = arr[i] + pref[i - 1];
        if(pref[i] == sum/2){
          return true;
        }
      }
      for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
          int x = pref[j] - pref[i];
          if(x == sum/2){
            return true;
          }
        }
      }
      return false;
    }
    int main(){
      int t;
      cin >> t;
      while(t--){
        bool b = solve();
        if(b){
          cout << "YES" << endl;
        }else{
          cout << "NO" << endl;
        }
      }
    }
