    #include <iostream>
    using namespace std;
    const int MOD = 1000000007;
    int main(){
      int n;
      cin >> n;
      string s;
      cin >> s;
      if(s.length() < 3){
        cout << 0 << endl;
        return 0;
      }
      long long a,ab,abc;
      a = ab = abc = 0;
      long long sc = 1;
      for(int i = 0; i < n; i++){
        if(s[i] == 'a'){
          a += sc;
        }
        if(s[i] == 'b'){
          ab += a;
        }
        if(s[i] == 'c'){
          abc += ab;
        }
        if(s[i] == '?'){
          abc = 3 * abc + ab;
          ab = 3 * ab + a;
          a = 3 * a + sc;
          sc = 3 * sc;
        }
        a %= MOD;
        ab %= MOD;
        abc %= MOD;
        sc %= MOD;
      }
      cout << abc << endl;
    }
