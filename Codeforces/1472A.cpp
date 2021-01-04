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
      int x,y;
      cin >> x >> y;
      long long prod = largest2(x) * largest2(y);
      int n;
      cin >> n;
      if(prod >= n){
        return true;
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
