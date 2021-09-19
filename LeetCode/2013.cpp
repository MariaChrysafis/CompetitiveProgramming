class DetectSquares {
public:
    vector<vector<int>> points;
    long long appears[1001][1001];
    DetectSquares() {
        for(int i = 0; i < 1001; i++) {
            for(int j = 0; j < 1001; j++) {
                appears[i][j] = 0;
            }
        }
    }
    
    void add(vector<int> point) {
        points.push_back(point);
        appears[point[0]][point[1]]++;
    }
    
    long long count(vector<int> point) {
        long long cntr = 0;
        for(int i = 0; i < points.size(); i++) {
            if(points[i][0] == point[0]) continue;
            if(points[i][1] == point[1]) continue;
            if(abs(points[i][0] - point[0]) != abs(points[i][1] - point[1])) continue;
            if(appears[points[i][0]][point[1]] && appears[point[0]][points[i][1]]) {
                cntr += appears[points[i][0]][point[1]] * appears[point[0]][points[i][1]];
            }
        }
        return cntr;
    }
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */
