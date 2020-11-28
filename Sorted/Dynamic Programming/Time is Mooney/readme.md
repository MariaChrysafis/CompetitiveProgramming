From the input, it's easy to see what cities we could have visited before visiting city x. Let adj[x] map a city x to the cities y such that we can go from y to x in 1 unit of itime.

Let's take a DP-approach. Let DP[i][j] be the maximum number of moonies someone can have after i units of time and ending at city j. We can compute dp[0][j] pretty easily. Now, note that when i is not 0, DP[i][j] = max(dp[i - 1][k] + moonie[j],DP[i][j]) for all k in adj[j]. This is becuase the only way to get to city j is by visiting something in adj[j].

And that's all!
