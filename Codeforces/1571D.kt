
import java.util.*
import java.io.*

    fun main(args: Array<String>) {
        val sc = Scanner(System.`in`)
        val n = sc.nextInt()
        val m = sc.nextInt()
        val hm1 = IntArray(n + 1)
        val hm2 = IntArray(n + 1)
        val hm = IntArray(1001 * n + n + 1)
        for (i in hm1.indices) {
            hm2[i] = 0
            hm1[i] = hm2[i]
        }
        for (i in hm.indices) {
            hm[i] = 0
        }
        var f = 0
        var l = 0
        for (i in 0 until m) {
            val a = sc.nextInt()
            val b = sc.nextInt()
            if (i != 0) {
                hm1[a]++
                hm2[b]++
                hm[1001 * a + b]++
            } else {
                f = a
                l = b
            }
        }
        var myMax = 0
        for (i in 1..n) {
            for (j in 1..n) {
                if (i == j) continue
                var ans = 0
                val c1 = hm1[i] + hm2[j] - 2 * hm[1001 * i + j]
                val c2 = hm[1001 * i + j]
                val c0 = n - 1 - c1 - c2
                ans = if (f == i && l == j) {
                    1
                } else if (f == i || l == j) {
                    c2 + 1
                } else {
                    c1 + c2 + 1
                }
                //System.out.println(ans);
                myMax = Math.max(myMax, ans)
            }
        }
        println(myMax)
    }
