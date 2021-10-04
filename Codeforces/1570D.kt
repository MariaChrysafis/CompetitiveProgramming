

import java.util.*
import kotlin.jvm.JvmStatic

    var cntr = 0
    var hs: MutableSet<Int> = HashSet()
    fun reachable(x: Int) {
        var x = x
        if (hs.contains(x)) {
            return
        }
        hs.add(x)
        //System.out.println(x);
        if (x == 0) {
            return
        }
        x++
        cntr++
        while (x % 10 == 0) {
            x /= 10
        }
        reachable(x)
    }
    fun main(args: Array<String>) {
        val sc = Scanner(System.`in`)
        val x = sc.nextInt()
        reachable(x)
        println(cntr)
    }
