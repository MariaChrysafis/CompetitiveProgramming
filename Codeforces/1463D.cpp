#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void solve(){
  int n;
  cin >> n;
  vector<int> v1(n);
  vector<int> v2;
  bool flag[2 * n + 1];
  for(int i = 1; i <= 2 * n; i++){
    flag[i] = 0;
  }
  for(int i = 0; i < n; i++){
    cin >> v1[i];
    flag[v1[i]] = 1;
  }
  for(int i = 1; i <= 2 * n; i++){
    if(!flag[i]){
      v2.push_back(i);
    }
  }
  int j = -1;
  int a = 0;
  for(int i = 0; i < n; i++){
    int pj = j;
    if(j == -1){
      j = 0;
    }
    while(j < n && v2[j] < v1[i]){
      j++;
    }
    if(pj == j){
      j++;
    }
    if(j < n && v2[j] > v1[i]){
      a++;
    }
  }
  reverse(v1.begin(),v1.end());
  reverse(v2.begin(),v2.end());
  int b = 0;
  j = -1;
  for(int i = 0; i < n; i++){
    int pj = j;
    if(j == -1){
      j = 0;
    }
    while(j < n && v2[j] > v1[i]){
      j++;
    }
    if(pj == j){
      j++;
    }
    if(j < n && v2[j] < v1[i]){
      b++;
    }
  }
  //cout << a << " " << n - b << endl;
  //return;
  cout << a - (n - b) + 1 << endl;
}
int main(){
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
