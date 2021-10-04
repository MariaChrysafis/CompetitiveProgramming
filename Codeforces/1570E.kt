import java.util.*
import kotlin.jvm.JvmStatic

    fun compress(s: String): String {
        var hasSeenOne = false
        var str = ""
        for (i in 0 until s.length) {
            if (s[i] == '0' && hasSeenOne) {
                str = str + s[i]
            } else if (s[i] == '1') {
                str = str + s[i]
                hasSeenOne = true
            }
        }
        return str
    }

    fun reverse(s: String): String {
        var str = ""
        for (i in s.length - 1 downTo 0) {
            str = str + s[i]
        }
        return str
    }

    fun solve(s: String) {
        var str = compress(s)
        str = reverse(str)
        str = compress(str)
        //System.out.println(str);
        var cntr = 0
        for (i in 0 until str.length) {
            if (str[i] == '0') {
                cntr++
            }
        }
        println(cntr)
    }

    fun main(args: Array<String>) {
        val sc = Scanner(System.`in`)
        val t = sc.nextInt()
        for (i in 0 until t) {
            val s = sc.next()
            solve(s)
        }
    }
