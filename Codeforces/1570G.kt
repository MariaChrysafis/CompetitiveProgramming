import java.util.*
import java.io.*

    fun main(args: Array<String>) {
        //val positions = Array(k) { LongArray(m) { jin.nextInt().toLong() } }
        val sc = Scanner(System.`in`)
        print("? ")
        for (i in 1..100) {
            print(i)
            print(" ")
        }
        val arr = IntArray(14)
        for (i in 0..13) {
            arr[i] = 0
        }
        println()
        val x = sc.nextInt()
        for (i in 7..13) {
            if (x and (1 shl i) > 0) {
                arr[i] = 1
            }
        }
        println()
        print("? ")
        for (i in 0..99) {
            print(i * 128)
            print(" ")
        }
        println()
        val y = sc.nextInt()
        for (i in 0..6) {
            if (y and (1 shl i) > 0) {
                arr[i] = 1
            }
        }
        var ans = 0
        for (i in 0..13) {
            ans += (1 shl i) * arr[i]
        }
        print("! ")
        print(ans)
    }
