class Solution {
public:
    struct Graph {
        vector<vector<int>> adj;
        set<int> vec;
        void bfs() {
            set<int> hasVisited[adj.size()];
            queue<pair<int,int>> q;
            q.push(make_pair(0, 0));
            while (!q.empty()) {
                int dist = q.front().first;
                int vertex = q.front().second;
                q.pop();
                if (hasVisited[vertex].size() >= 2) {
                    continue;
                }
                hasVisited[vertex].insert(dist);
                if (vertex == adj.size() - 1) {
                    //cout << dist << endl;
                    vec.insert(dist);
                    if (vec.size() == 2) return;
                }
                for (int i: adj[vertex]) {
                    q.push(make_pair(dist + 1, i));
                }
            }
        }
    };
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        Graph g;
        g.adj.resize(n);
        for (auto v: edges) {
            g.adj[v[0] - 1].push_back(v[1] - 1);
            g.adj[v[1] - 1].push_back(v[0] - 1);
        }
        g.bfs();
        int moves = *g.vec.rbegin(); //how many edges we have to cross
        cout << moves << endl;
        int lastMove = 0;
        bool flag = false;
        int cntr = 0;
        for (int i = 0; i <= 100000000; i++) {
            if (i % change == 0) {
                flag = !flag;
                if (!flag) i += (change - 1);
            }
            if (abs(i - lastMove) >= time && flag) {
                lastMove = i;
                cntr++;
                if (cntr == moves - 1) {
                    return i + time;
                }
            }
        }
        return 0;
    
    }
};
