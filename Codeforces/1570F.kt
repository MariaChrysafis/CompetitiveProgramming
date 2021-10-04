import java.io.*
import java.util.*
    fun main(args: Array<String>) {
        //val positions = Array(k) { LongArray(m) { jin.nextInt().toLong() } }
        val sc = Scanner(System.`in`)
        val n = sc.nextInt()
        val m = sc.nextInt()
        val a = Array(n) { IntArray(m) }
        val b = Array(n) { IntArray(m) }
        for (i in 0 until n) {
            for (j in 0 until m) {
                a[i][j] = sc.nextInt()
                b[i][j] = 0
            }
        }
        val x = ArrayList<Int>()
        val y = ArrayList<Int>()
        for (i in 0 until n) {
            for (j in 0 until m) {
                if (i != n - 1 && j != m - 1) {
                    if (a[i][j] == 1 && a[i + 1][j] == 1 && a[i][j + 1] == 1 && a[i + 1][j + 1] == 1) {
                        b[i + 1][j + 1] = 1
                        b[i][j + 1] = b[i + 1][j + 1]
                        b[i + 1][j] = b[i][j + 1]
                        b[i][j] = b[i + 1][j]
                        x.add(i + 1)
                        y.add(j + 1)
                    }
                }
            }
        }
        for (i in 0 until n) {
            for (j in 0 until m) {
                if (a[i][j] != b[i][j]) {
                    print("-1")
                    return
                }
            }
        }
        println(x.size)
        for (i in x.indices) {
            println(x[i].toString() + " " + y[i])
        }
    }
