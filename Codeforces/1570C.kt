import java.util.*
import java.io.*

    fun main(args: Array<String>) {
        //val positions = Array(k) { LongArray(m) { jin.nextInt().toLong() } }
        val sc = Scanner(System.`in`)
        val n = sc.nextInt()
        val a = arrayOfNulls<Pair>(n)
        for (i in 0 until n) {
            a[i] = Pair(sc.nextInt(), i)
        }
        for (i in 0 until n) {
            for (j in i + 1 until n) {
                if (a[j]!!.first > a[i]!!.first) {
                    var temp = a[i]!!.first
                    a[i]!!.first = a[j]!!.first
                    a[j]!!.first = temp
                    temp = a[i]!!.second
                    a[i]!!.second = a[j]!!.second
                    a[j]!!.second = temp
                }
            }
        }
        var ans = 0
        for (i in 0 until n) {
            ans += a[i]!!.first * i + 1
        }
        println(ans)
        for (i in 0 until n) {
            print(a[i]!!.second + 1)
            print(" ")
        }
    }

    class Pair(var first: Int, var second: Int)
