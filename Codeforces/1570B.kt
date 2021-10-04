import java.io.*
import java.util.*

    var a1 = 0
    var a2 = 0
    var k1 = 0
    var k2 = 0
    var n = 0
    var ans = 0
    fun take1() {
        a1--
        n -= k1
        ans++
    }

    fun take2() {
        a2--
        n -= k2
        ans++
    }
    
    fun main(args: Array<String>) {
        //val positions = Array(k) { LongArray(m) { jin.nextInt().toLong() } }
        val sc = Scanner(System.`in`)
        a1 = sc.nextInt()
        a2 = sc.nextInt()
        k1 = sc.nextInt()
        k2 = sc.nextInt()
        n = sc.nextInt()
        val o1: Int
        val o2: Int
        val o3: Int
        val o4: Int
        val o5: Int
        if (k1 > k2) {
            var temp = k1
            k1 = k2
            k2 = temp
            temp = a1
            a1 = a2
            a2 = temp
        }
        o1 = a1
        o2 = a2
        o3 = k1
        o4 = k2
        o5 = n
        ans = 0
        n -= (k1 - 1) * a1 + (k2 - 1) * a2
        print(Math.max(n, 0).toString() + " ")
        a1 = o1
        a2 = o2
        k1 = o3
        k2 = o4
        n = o5
        for (i in 0..9999) {
            if (a1 == 0 && a2 == 0) {
                break
            }
            if (a1 == 0) {
                if (n >= k2) {
                    take2()
                } else {
                    break
                }
            } else {
                if (n >= k1) {
                    take1()
                } else {
                    break
                }
            }
        }
        print(ans)
    }
