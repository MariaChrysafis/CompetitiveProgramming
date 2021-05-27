#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
const int maxN = 1e2 + 9;
const int maxK = 1e5 + 9;
int dp[2][maxK];
int N, K;
vector<int> arr;
bool memoize(int first, int x){
    if(dp[first][x] != -1){
        return dp[first][x];
    }
    bool b;
    b = false;
    for(int i: arr){
        if(x - i >= 0){
            if(first) b = b || memoize(1 - first, x - i);
            else b = b || !memoize(1 - first, x - i);
        }
    }
    if(first) dp[first][x] = (int)b;
    else dp[first][x] = !b;
    //cout << b << endl;
    return dp[first][x];
}
int main(){
    cin >> N >> K;
    arr.resize(N);
    for(int i = 0; i < N; i++) cin >> arr[i];
    for(int i = 0; i < maxK; i++){
        dp[0][i] = dp[1][i] = -1;
    }
    bool b = memoize(true, K);
    if(b) cout << "First";
    else cout << "Second";
}
