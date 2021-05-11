    #include <iostream>
    #include <vector>
    using namespace std;
    vector<int> v;
    void fill(){
        for(int i = 1; i < 10000; i++){
            if(i % 6 == 0 || i % 10 == 0 || i % 15 == 0){
                v.push_back(i);
            }
        }
    }
    int main(){
        fill();
        //cout << v.size() << endl;
        int N;
        cin >> N;
        if(N == 3){
            cout << "6 10 15" << endl;
            return 0;
        }
        for(int i = 0; i < N; i++) cout << v[i] << " ";
    }
