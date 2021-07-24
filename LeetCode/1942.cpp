class Solution {
public:
    struct element{
        int ind;
        int time;
        bool b;
    };
    static bool comp(element e1, element e2){
        if(e1.time == e2.time) return (e1.b > e2.b);
        return (e1.time < e2.time);
    }
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        set<int> unoccupied;
        for(int i = 0; i < times.size() + 3; i++){
            unoccupied.insert(i);
        }
        vector<element> v; //0 -> starting; 1 -> leaving
        for(int i = 0; i < times.size(); i++){
            v.push_back({i, times[i][0], 0});
            v.push_back({i, times[i][1], 1});
            //cout << times[i][0] << " " << times[i][1] << endl;
        }
        sort(v.begin(), v.end(), comp);
        for(element e: v){
            cout << e.time << ' ';
        }
        cout << endl;
        map<int,int> chair;
        for(element p: v){
            if(p.b == 0){
                //starting
                int x = *unoccupied.begin();
                chair[p.ind] = x;
                unoccupied.erase(unoccupied.begin());
            }else{
                unoccupied.insert(chair[p.ind]);
            }
        }
        return chair[targetFriend];
    }
};
