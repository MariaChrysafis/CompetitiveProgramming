import java.util.*
import java.io.*

    fun solve(n: Int, a: Int, va: Int, c: Int, vc: Int, b: Int) {
        if (va == vc) {
            println(va)
            return
        }
        val arr = IntArray(101)
        for (i in 1..a) {
            arr[i] = Math.min(i, va)
        }
        for (i in a + 1 until c) {
            arr[i] = Math.min(arr[i - 1] + 1, vc)
        }
        println(arr[b])
    }

    fun main(args: Array<String>) {
        //val positions = Array(k) { LongArray(m) { jin.nextInt().toLong() } }
        val sc = Scanner(System.`in`)
        val t = sc.nextInt()
        for (tc in 1..t) {
            val n = sc.nextInt()
            val a = sc.nextInt()
            val va = sc.nextInt()
            val c = sc.nextInt()
            val vc = sc.nextInt()
            val b = sc.nextInt()
            solve(n, a, va, c, vc, b)
        }
    }
