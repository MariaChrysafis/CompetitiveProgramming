#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
void solve(){
  int n;
  cin >> n;
  int arr[n];
  map<int,int> myMap;
  map<int,int> ind;
  for(int i = 0; i < n; i++){
    cin >> arr[i];
    ind[arr[i]] = i;
    myMap[arr[i]]++;
  }
  sort(arr, arr + n);
  for(int i = 0; i < n; i++){
    if(myMap[arr[i]] == 1){
      cout << ind[arr[i]] + 1 << endl;
      return;
    }
  }
  cout << -1 << endl;
}
int main(){
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
