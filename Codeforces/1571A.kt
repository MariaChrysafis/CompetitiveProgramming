

import java.util.*
import java.io.*


    fun solve(s: String) {
        var l = 0
        var e = 0
        var g = 0
        for (i in 0 until s.length) {
            if (s[i] == '<') l++
            if (s[i] == '>') g++
            if (s[i] == '=') e++
        }
        if (l == 0 && g == 0) {
            println('=')
        } else if (l == 0) {
            println('>')
        } else if (g == 0) {
            println('<')
        } else {
            println('?')
        }
    }

    fun main(args: Array<String>) {
        //val positions = Array(k) { LongArray(m) { jin.nextInt().toLong() } }
        val sc = Scanner(System.`in`)
        val t = sc.nextInt()
        for (tc in 1..t) {
            val s = sc.next()
            solve(s)
        }
    }
