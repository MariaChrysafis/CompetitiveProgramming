

        #include <iostream>
        #include <unordered_map>
        #include <algorithm>
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
        int solve(){
          //says if Alice wins
          int n;
          cin >> n;
          vector<int> v(n);
          for(int i = 0; i < n; i++){
            cin >> v[i];
          }
          vector<int> odd;
          vector<int> even;
          for(int i = 0; i < n; i++){
            if(v[i] % 2 == 0){
              even.push_back(v[i]);
            }else{
              odd.push_back(v[i]);
            }
          }
          sort(odd.begin(),odd.end()); reverse(odd.begin(),odd.end());
          sort(even.begin(),even.end()); reverse(even.begin(),even.end());
          int oddInd = 0;
          int evenInd = 0;
          long long a = 0;
          long long b = 0;
          for(int i = 0; i < n; i++){
            if(i % 2 == 0){
              //Alice's move
              if(evenInd == even.size()){
                oddInd++;
                continue;
              }
              if(oddInd == odd.size()){
                a += even[evenInd];
                evenInd++;
                continue;
              }
              if(even[evenInd] < odd[oddInd]){
                oddInd++;
              }else{
                a += even[evenInd];
                evenInd++;
              }
            }else{
              //Bob's move
              if(evenInd == even.size()){
                b += odd[oddInd];
                oddInd++;
                continue;
              }
              if(oddInd == odd.size()){
                evenInd++;
                continue;
              }
              if(even[evenInd] < odd[oddInd]){
                oddInd++;
                b += odd[oddInd - 1];
              }else{
                evenInd++;
              }
            }
          }
          if(a == b){
            return 3;
          }
          return (a > b);
        }
        int main(){
          ios_base::sync_with_stdio(false);
          cin.tie(NULL);
          int t;
          cin >> t;
          while(t--){
            int b = solve();
            if(b == 3){
              cout << "Tie" << endl;
              continue;
            }
            if(b == 1){
              cout << "Alice" << endl;
            }else{
              cout << "Bob" << endl;
            }
          }
        }
