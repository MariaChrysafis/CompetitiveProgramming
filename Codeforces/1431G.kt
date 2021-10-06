import java.util.*
import java.io.*


    fun main(args: Array<String>) {
        val sc = Scanner(System.`in`)
        val n = sc.nextInt()
        val k = sc.nextInt()
        val arr = IntArray(n)
        for (i in 0 until n) {
            arr[i] = sc.nextInt()
        }
        Arrays.sort(arr)
        val dp = Array(n) { IntArray(n) }
        for (i in n - 1 downTo 0) {
            for (j in i + 1 until n) {
                if (j % 2 == i % 2) {
                    dp[i][j] = 0
                } else {
                    if (j - i == 1) {
                        dp[i][j] = arr[j] - arr[i]
                    } else {
                        dp[i][j] = dp[i + 1][j - 1] + arr[j] - arr[i]
                    }
                }
            }
        }
        val ans = Array(n) { IntArray(n + 1) }
        for (i in 0 until n) {
            var j = 0
            while (j <= n) {
                if (j > i + 1 || j == 0) {
                    ans[i][j] = 0
                    j += 2
                    continue
                }
                if (i + 1 == j) {
                    ans[i][j] = dp[0][i]
                    j += 2
                    continue
                }
                ans[i][j] = ans[i - 1][j]
                for (l in 1..i) {
                    if (j - (i - l + 1) >= 0) {
                        ans[i][j] = Math.max(dp[l][i] + ans[l - 1][j - (i - l + 1)], ans[i][j])
                    }
                }
                j += 2
            }
        }
        println(ans[n - 1][2 * k])
    }
