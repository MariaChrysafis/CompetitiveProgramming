class Solution {
public:
    struct interval{
        long long l;
        long long r;
        long long color;
    };
    struct point{
        long long l;
        long long color;
        bool b; //0 if left, 1 if right
    };
    static bool comp(point p1, point p2){
        if(p1.l == p2.l) return (p1.b > p2.b);
        return (p1.l < p2.l);
    }
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        vector<interval> intervals;
        vector<point> v;
        v.push_back({-1, 0, 0});
        for(int i = 0; i < segments.size(); i++){
            intervals.push_back({segments[i][0], segments[i][1], segments[i][2]});
            v.push_back({segments[i][0], segments[i][2], 0});
            v.push_back({segments[i][1], segments[i][2], 1});
        }
        sort(v.begin(), v.end(), comp);
        long long cur = 0;
        map<long long,long long> myMap;
        for(int i = 0; i < v.size(); i++){
            if(v[i].b == 0){
                //this is a left poitn
                cur += v[i].color;
            }else{
                cur -= v[i].color;
            }
            myMap[v[i].l] = cur;
            //cout << cur << " ";
        }
        vector<pair<long long,long long>> vec;
        for(pair<long long,long long> p: myMap){
            vec.push_back(p);
        }
        long long l = v[1].l;
        vector<vector<long long>> ans;
        for(int i = 2; i < vec.size(); i++){
            ans.push_back({l, vec[i].first, vec[i - 1].second});
            l = vec[i].first;
        }
        vector<vector<long long>> arr;
        for(int i = 0; i < ans.size(); i++){
            if(ans[i].back() == 0) continue;
            arr.push_back(ans[i]);
        }
        return arr;
    }
};
