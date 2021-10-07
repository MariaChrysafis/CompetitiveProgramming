import java.lang.StringBuilder
import java.util.*
import java.io.*


    fun change(s1: String, s2: String): Int {
        var cntr = 0
        for (i in 0 until s1.length) {
            if (s1[i] != s2[i]) {
                cntr++
            }
        }
        return cntr
    }

    fun solve(n: Int, s1: String?, s2: String): Int {
        for (i in 0 until s2.length - 1) {
            if (s2[i] == '1' && s2[i + 1] == '1') {
                return -1
            }
        }
        for (i in 0 until s2.length - 3) {
            if (s2[i] == '1' && s2[i + 3] == '1') {
                return -1
            }
        }
        val str = StringBuilder(s1)
        var ans = 0
        for (i in 0 until s2.length) {
            if (s2[i] == '0') continue
            if (i >= 2 && s2[i - 2] == '1') {
                val pocket = "" + str[i] + str[i + 1] + str[i + 2] + str[i + 3]
                val des = "()()"
                ans += change(des, pocket)
                str.setCharAt(i, '(')
                str.setCharAt(i + 1, ')')
                str.setCharAt(i + 2, '(')
                str.setCharAt(i + 3, ')')
            } else if (i + 2 < s2.length && s2[i + 2] == '1') {
                val pocket = "" + str[i] + str[i + 1] + str[i + 2] + str[i + 3]
                val des = "()()"
                ans += change(des, pocket)
                str.setCharAt(i, '(')
                str.setCharAt(i + 1, ')')
                str.setCharAt(i + 2, '(')
                str.setCharAt(i + 3, ')')
            } else {
                val pocket = "" + str[i] + str[i + 1] + str[i + 2] + str[i + 3]
                val des1 = "()()"
                val des2 = "(())"
                ans += Math.min(change(des1, pocket), change(des2, pocket))
            }
        }
        return ans
    }

    fun main(args: Array<String>) {
        val sc = Scanner(System.`in`)
        val t = sc.nextInt()
        for (i in 1..t) {
            val n = sc.nextInt()
            val s1 = sc.next()
            val s2 = sc.next()
            println(solve(n, s1, s2))
        }
    }
