#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
void solve(){
  long long orig;
  long long n;
  cin >> n;
  orig = n;
  //vector<pair<long long,long long>>v;
  long long arr[60];
  for(int i = 0; i < 60; i++) arr[i] = 1;
  for(long long i = 2; i * i <= orig; i++){
    long long cntr = 0;
    while(n % i == 0){
      n /= i;
      cntr++;
    }
    for(int j = 0; j < cntr; j++){
      arr[j] *= i;
    }
  }
  if(n == orig){
    cout << 1 << endl;
    cout << orig << endl;
    return;
  }
  //cout << n << endl;
  if(n != 1){
    arr[0] *= n;
    //cout << arr[0] << endl;
    //return;
  }
  vector<long long> answ;
  for(int i = 0; i < 60; i++){
    if(arr[i] == 1) break;
    answ.push_back(arr[i]);
  }
  reverse(answ.begin(),answ.end());
  cout << answ.size() << endl;
  for(long long i: answ){
    cout << i << " ";
  }
  cout << endl;
}
int main(){
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
