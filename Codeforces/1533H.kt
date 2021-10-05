import java.util.*
import java.io.*
    fun numSubmat(mat: Array<Array<Boolean?>>): Long {
        val m = mat.size
        val n: Int = mat[0].size
        var ans = 0L
        val h = IntArray(n)
        for (i in 0 until m) {
            val idxQ = ArrayDeque<Int>()
            val sumQ = ArrayDeque<Int>()
            idxQ.addFirst(-1)
            sumQ.addFirst(0)
            for (j in 0 until n) {
                h[j] = if (!mat[i][j]!!) 0 else h[j] + 1
            }
            for (j in 0 until n) {
                var sum = 0
                while (idxQ.peekFirst() >= 0 && h[idxQ.peekFirst()] >= h[j]) {
                    idxQ.removeFirst()
                    sumQ.removeFirst()
                }
                sum += h[j] * (j - idxQ.peekFirst()) + sumQ.peekFirst()
                idxQ.addFirst(j)
                sumQ.addFirst(sum)
                ans += sum.toLong()
            }
        }
        return ans
    }

    fun grid(arr: Array<String?>, x: Int): Array<Array<Boolean?>> {
        val hm = HashMap<Char, Boolean>()
        var c = 'A'
        for (i in 0..4) {
            hm[c] = x and (1 shl i) > 0
            c++
        }
        val ans = Array(arr.size) {
            arrayOfNulls<Boolean>(
                arr[0]!!.length
            )
        }
        for (i in ans.indices) {
            for (j in 0 until ans[i].size) {
                ans[i][j] = hm[arr[i]!![j]]
            }
        }
        return ans
    }
    fun main(args: Array<String>) {
        val sc = Scanner(System.`in`)
        val n = sc.nextInt()
        val m = sc.nextInt()
        val arr = arrayOfNulls<String>(n)
        for (i in 0 until n) {
            arr[i] = sc.next()
        }
        val dp = LongArray(32)
        for (i in 0..31) {
            val myGrid = grid(arr, i)
            dp[i] = numSubmat(myGrid)
        }
        val ans = LongArray(32)
        val `val` = LongArray(6)
        for (i in 0..31) {
            ans[i] = 0L
        }
        for (i in 0..5) {
            `val`[i] = 0L
        }
        for (i in 0..31) {
            ans[i] = dp[i]
            if (dp[i] == 0L) {
                continue
            }
            var s = i
            while (true) {
                if (s != i) {
                    if ((Integer.bitCount(i) - Integer.bitCount(s)) % 2 == 1) {
                        ans[i] = ans[i] - dp[s]
                    } else {
                        ans[i] = ans[i] + dp[s]
                    }
                }
                if (s == 0) {
                    break
                }
                s = s - 1 and i
            }
            `val`[Integer.bitCount(i)] += ans[i]
        }
        for (i in 1 until `val`.size) {
            print(`val`[i].toString() + " ")
        }
    }
