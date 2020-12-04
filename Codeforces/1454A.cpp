#include <iostream>
using namespace std;
void solve(){
  int n;
  cin >> n;
  for(int i = 1; i <= n; i++){
    cout << i % n + 1 << " ";
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
