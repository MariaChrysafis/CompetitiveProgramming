#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;
template<typename T>
void pop_front(std::vector<T> &v)
{
  if (v.size() > 0) {
    v.erase(v.begin());
  }
}
class Problem2Dishwashing {
public:
  vector<deque<int>> counter;
  vector<int> remap(vector<int> vec) {
    vector<pair<int, int>> ind;
    for (int i = 0; i < vec.size(); i++) {
      ind.push_back({vec[i], i});
    }
    sort(ind.begin(), ind.end());
    vector<int> ans(vec.size());
    for (int i = 0; i < ind.size(); i++) {
      ans[ind[i].second] = i;
    }
    return ans;
  }
  deque<int> create(int x){
    deque<int> d;
    d.push_back(x);
    return d;
  }
  int best(int des){
    for(int i = 0; i < counter.size(); i++){
      if(!counter[i].empty()){
        int x = counter[i].back();
        if(des < x){
          return i;
        }
      }
    }
    return -1;
  }
  bool valid(vector<int> vec){
    counter.clear();
    int ind = 0; /* the index of the first non-empty deque */
    int x = 0; /* the smallest unpicked one */
    vec = remap(vec);
    int dum = 0;
    while(dum < vec.size() && vec[dum] == dum){
      dum++;
      x++;
    }
    for(int i = dum; i < vec.size(); i++){
      if(vec.size() == 25){
        //cout << vec[i] << " " << counter.size() << endl;
      }
      //cout << i << endl;
      if(counter.empty()){
        counter.push_back(create(vec[i]));
        continue;
      }
      if(counter[ind].empty()){
        //there's nothing for Elsie to do
        counter[ind] = create(vec[i]);
        continue;
      }
      if(vec[i] == x){
        //we give the plate to Elsie and as many other plates as we can to her
        x++;
        while(!counter[ind].empty() && counter[ind].back() == x){
          x++;
          counter[ind].pop_back();
          if(counter[ind].empty()){
            if(counter.size() > ind + 1){
              ind++;
            }
          }
        }
        continue;
      }
      //We place the plate in some other stack
      if(best(vec[i]) == -1){
        counter.push_back(create(vec[i]));
      }else{
        counter[best(vec[i])].push_back(vec[i]);
      }
    }
    vector<int> myVec;
    for(int i = 0; i < counter.size(); i++){
      deque<int> d = counter[i];
      while(!d.empty()){
        int a = d.front();
        myVec.push_back(a);
        d.pop_front();
        if(vec.size() == 25){
          //cout << myVec[i] << " ";
        }
      }
    }
    vector<int> temp = myVec;
    sort(temp.begin(),temp.end());
    return (temp == myVec);
  }
  void solve(std::istream &in, std::ostream &out) {
    int n;
    in >> n;
    vector<int> v;
    for(int i = 0; i < n; i++){
      int a;
      in >> a;
      v.push_back(a);
      //cout << i << endl;
      if(!valid(v)){
        out << i;
        return;
      }
    }
    out << n << endl;
  }
};
