

import java.lang.StringBuilder
import java.util.*
import java.io.*

    fun reverse(s1: String?): String {
        val st = StringBuilder(s1)
        st.reverse()
        return st.toString()
    }

    fun solve(arr: ArrayList<Line>): Int {
        var myMin = 1e9.toInt()
        for (l in arr) {
            val s1 = reverse(l.s1)
            val s2 = reverse(l.s2)
            var cntr = 0
            for (i in 0 until Math.min(s1.length, s2.length)) {
                if (s1[i] == s2[i]) {
                    cntr++
                } else {
                    break;
                }
            }
            myMin = Math.min(myMin, cntr)
        }
        return myMin
    }

    fun badSolver(arr: ArrayList<Line>): Int {
        var myMax = 0
        for (l in arr) {
            val s1 = reverse(l.s1)
            val s2 = reverse(l.s2)
            var cntr = 0
            for (i in 0 until Math.min(s1.length, s2.length)) {
                if (s1[i] == s2[i]) {
                    cntr++
                } else {
                    break;
                }
            }
            myMax = Math.max(myMax, cntr + 1)
        }
        return myMax
    }
    fun main(args: Array<String>) {
        //val positions = Array(k) { LongArray(m) { jin.nextInt().toLong() } }
        val sc = Scanner(System.`in`)
        val t = sc.nextInt()
        for (tc in 1..t) {
            val n = sc.nextInt()
            val arr = ArrayList<Line>()
            val barr = ArrayList<Line>()
            for (i in 0 until n) {
                var s1: String?
                var s2: String?
                s1 = sc.next()
                s2 = sc.next()
                val b = sc.nextInt() > 0
                if (b) {
                    arr.add(Line(s1, s2, b))
                } else {
                    barr.add(Line(s1, s2, b))
                }
            }
            val x = badSolver(barr)
            val y = solve(arr)
            val vec = ArrayList<Int>()
            for (i in x..y) {
                //System.out.print(i + " ");
                vec.add(i)
            }
            println(vec.size)
            for (i in vec.indices) {
                print(vec[i].toString() + " ")
            }
            println()
        }
    }

    class Line(var s1: String?, var s2: String?, var flag: Boolean)
