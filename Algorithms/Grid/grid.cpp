struct Grid {
    vector<vector<ll>> grid;
    vector<vector<ll>> sums;
    ll find_sum (int l1, int r1, int l2, int r2) {
        return sums[l2 + 1][r2 + 1] - sums[l2 + 1][r1] - sums[l1][r2 + 1] + sums[l1][r1];
    }
    void fill () {
        sums.resize(grid.size() + 1);
        for (int i = 0; i < sums.size(); i++) {
            sums[i].resize(grid[0].size() + 1);
        }
        sums[0][0] = 0;
        for (int i = 1; i < sums.size(); i++) {
            sums[i][0] = 0;
        }
        for (int i = 1; i < sums[0].size(); i++) {
            sums[0][i] = 0;
        }
        for (int i = 1; i < sums.size(); i++) {
            for (int j = 1; j < sums[0].size(); j++) {
                sums[i][j] = sums[i][j - 1] + sums[i - 1][j] - sums[i - 1][j - 1] + grid[i - 1][j - 1];
            }
        }
    }
    void resz (int n, int m) {
        grid.resize(n);
        for (int i = 0; i < n; i++) {
            grid[i].resize(m);
        }
    }
};
