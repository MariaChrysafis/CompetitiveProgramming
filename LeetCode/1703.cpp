class Solution {
public:
  vector<long long> pref;
  long long sum(int l, int r){
    if(r > pref.size() - 1){
      r = pref.size() - 1;
    }
    if(r < l){
      return 0;
    }
    if(l <= 0){
      return pref[r];
    }
    return pref[r] - pref[l - 1];
  }
  int minMoves(vector<int>& nums, int k) {
    vector<int> v; /*  stores the positions of all of the ones */
    for(int i = 0; i < nums.size(); i++){
      if(nums[i] == 1){
        v.push_back(i);
      }
    }
    pref.resize(nums.size());
    pref[0] = v[0];
    for(int i = 1; i < v.size(); i++){
      pref[i] = pref[i - 1] + v[i];
    }
    long long myMin = 10000000000;
    if(k == 1){
      return 0;
    }
    for(int i = 0; i < v.size(); i++){
      //[i, i + k - 1]
      if(i + k - 1 == v.size()){
        break;
      }
      if(k % 2 == 1){
        int mid = (2 * i + k)/2;
        long long a = sum(mid + 1, i + k - 1) - sum(i, mid - 1);
        cout << a << endl;
        myMin = min(a, myMin);
      }else{
        int mid = (2 * i + k + 1)/2;
        long long a = sum(mid + 1, i + k - 1) - sum(i, mid - 1) + v[mid];
        cout << a << endl;
        myMin = min(a, myMin);
      }
    }
    cout << "---------------" << endl;
    //return myMin;
    if(k % 2 == 1){
      long long l = k/2;
      return myMin - l * (l + 1);
    }else{
      long long l = k/2;
      long long r = (k - 1)/2;
      return myMin - r * (r + 1)/2 - l * (l + 1)/2;
    }
  }
};
