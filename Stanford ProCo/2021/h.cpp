#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> alice;
vector<int> bob;
int play(){
    int a = 0;
    int b = 0;
    int ans = 0;
    while(a < alice.size() && b < bob.size()){
        if(alice[a] < bob[b]){
            a++;
        }else{
            a++, b++;
            ans++;
        }
    }
    return ans;
}
int main(){
    //alice wants to get better than bob
    int n;
    cin >> n;
    alice.resize(n), bob.resize(n);
    for(int i = 0; i < n; i++) cin >> alice[i];
    for(int i = 0; i < n; i++) cin >> bob[i];
    sort(alice.begin(), alice.end());
    sort(bob.begin(), bob.end());
    cout << play() << endl;
}
