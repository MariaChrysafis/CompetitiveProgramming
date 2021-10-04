package com.company

import java.util.*
import kotlin.jvm.JvmStatic

object Main {
    @JvmStatic
    fun main(args: Array<String>) {
        val sc = Scanner(System.`in`)
        val t = sc.nextInt()
        for (i in 0 until t) {
            val x = sc.nextInt()
            val y = sc.nextInt()
            println(x + y)
        }
    }
}
