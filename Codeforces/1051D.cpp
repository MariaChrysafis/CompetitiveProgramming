#include <iostream>
using namespace std;
#define ll long long
int main(){
  const int MOD = 998244353;
  int n,k;
  cin >> n >> k;
  ll ww[n + 1][k + 1];
  ll wb[n + 1][k + 1];
  ll bw[n + 1][k + 1];
  ll bb[n + 1][k + 1];
  //ww[0] = bb[0] = bw[0] = wb[0] = 0;
  //cout << "    ww wb" << endl;
  for(int i = 0; i <= n; i++){
    for(int j = 0; j <= k; j++){
      if(2 * i < j){
        ww[i][j] = 0;
        wb[i][j] = 0;
        bw[i][j] = 0;
        bb[i][j] = 0;
        continue;
      }
      if(i == 0 || j == 0){
        ww[i][j] = 0;
        bw[i][j] = 0;
        wb[i][j] = 0;
        bb[i][j] = 0;
        //cout << i << " " << j << " " << ww[i][j] << " " << wb[i][j] << endl;
        continue;
      }
      if(i == 1 && j != 1){
        if(j == 2){
          ww[i][j] = 0;
          bb[i][j] = 0;
          wb[i][j] = 1;
          bw[i][j] = 1;
          //cout << i << " " << j << " " << ww[i][j] << " " << wb[i][j] << endl;
          continue;
        }else{
          wb[i][j] = 0;
          bb[i][j] = 0;
          bw[i][j] = 0;
          wb[i][j] = 0;
          //cout << i << " " << j << " " << ww[i][j] << " " << wb[i][j] << ends;
          continue;
        }
      }
      if(j == 1){
        wb[i][j] = 0;
        bw[i][j] = 0;
        bb[i][j] = 1;
        ww[i][j] = 1;
        //cout << i << " " << j << " " << ww[i][j] << " " << wb[i][j] << endl;
        continue;
      }
      ww[i][j] = bb[i - 1][j - 1] + wb[i - 1][j] + bw[i - 1][j] + ww[i - 1][j];
      wb[i][j] = ww[i - 1][j - 1] + bb[i - 1][j - 1] + bw[i - 1][j - 2] + wb[i - 1][j];
      bw[i][j] = wb[i][j];
      bb[i][j] = ww[i][j];
      //cout << i << " " << j << " " << ww[i][j] << " " << wb[i][j] << endl;
      ww[i][j] %= MOD;
      bb[i][j] %= MOD;
      bw[i][j] %= MOD;
      wb[i][j] %= MOD;
    }
  }
  ll x = (ww[n][k] * 2 + wb[n][k] * 2) % MOD;
  cout << x << endl;
  return 0;
}
