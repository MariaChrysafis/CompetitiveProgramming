Let our moves be represented in the 0-indexed array arr.

This is clearly a dynamic programming problem. If this isn't immediately obvious, then work through the case when K = 1 (in fact, this is the silver version of the problem, which uses prefix sums). 

Let's try to find the state. It would probably be useful to know how far into the game we are. That is, we need to know how many moves in we are, which can be anything from 0 to N. We also probably want to know how many times we've switched our gesture, which can be anything from 0 to K. Lastly, it would be of use to know what our last gesture was.

We've found our state. Let DP[i][j][k] represent the maximum number of games Bessie can win if we've changed gestures i times, we're j moves in, and our last move is k. Note that k is a number, so let's map H, P, S to a number(1). Our mapping doesn't really matter; that is, so long as H,P,S are distinct numbers from 0 to 2, we're fine.

Let's work with the edge cases: dp[0][0][k] is clearly 0. When j = 0, we know that we've made 0 changes to our gesture; we can easily calculate that. If i = 0, then dp[i][j][k] = 0.

Now, onto the meat of the problem: the transitions. DP[i][j][k] can be equal to DP[i][j - 1][k] + (k beats arr[j - 1]). This is basically saying that we can always continue down the same path as before and keep the same move we did the previous time. But what if we want to change moves? Let's say we want to change our move from k1 to k. Then, DP[i][j][k] = DP[i - 1][j - 1][k1] + (k1 beats arr[j - 1]). We can say the same thign if we want to change our move from k2 to k.

And that's all.

(1) In my case, I used R, P, S and converted the input to R,P,S, and then converted R, P, S to numbers (for convenience purposes). But this is a neglible change.
