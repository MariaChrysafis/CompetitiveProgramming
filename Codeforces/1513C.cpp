#include <iostream>
#include <string>
const int maxN = 400005;
const int MOD = 1000000007;
using namespace std;
int arr[maxN];
void process(){
    for(int i = 0; i <= 9; i++){
        arr[i] = 1;
    }
    arr[10] = 2;
    for(int i = 11; i < maxN; i++){
        arr[i] = arr[i - 10] + arr[i - 9];
		if(arr[i] > MOD){
			arr[i] -= MOD;
		}
    }
}
void solve(){
	int n;
	cin >> n;
    string s = to_string(n);
    int m;
    cin >> m;
    int ans = 0;
	//cout << s << endl;
    for(int i = 0; i < s.length(); i++){
        int digit = s[i] - '0';
        ans += arr[m + digit];
		ans %= MOD;
    }
    cout << ans << '\n';
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
    int t;
    cin >> t;
    process();
    while(t--){
        solve();
    }
}
