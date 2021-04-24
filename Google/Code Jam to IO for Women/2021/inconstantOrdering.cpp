#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
char to_char(int x){
	return 'A' + x;
}
vector<int> beautify(vector<int> v){
	int myMin = v[0];
	for(int i: v){
		myMin = min(myMin, i);
	}
	for(int i = 0; i < v.size(); i++){
		v[i] -= myMin;
	}
	return v;
}
string solve(char c, int a, int b){
	//total string length is a + b;
	//up by a and then down by b
	vector<int> ans;
	ans.push_back(c - 'A');
	for(int i = 0; i < a; i++){
		ans.push_back(ans.back() + 1);
	}
	ans[ans.size() - 1] = max(ans[ans.size() - 1], b);
	if(b != 0) ans.push_back(b - 1);
	for(int i = 1; i < b; i++){
		ans.push_back(ans.back() - 1);
	}
	string s;
	for(int i = 1; i < ans.size(); i++){
		//cout << ans[i] << " ";
		s += 'A' + ans[i];
	}
	return s;
}
string merge(){
	int n;
	cin >> n;
	int arr[n];
	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}
	string s;
	for(int i = 0; i < n/2; i++){
		s += solve('A',arr[2 * i], arr[2 * i + 1]);
	}
	if(n % 2 == 1){
		s += solve('A', arr[n - 1], 0);
	}
	return s;
}
int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
    	cout << "Case #" << i + 1 << ": "; 
    	string s = merge();
    	cout << 'A' << s << endl;
    }
}
