import java.util.*
import java.io.*
    fun main(args: Array<String>) {
        //val positions = Array(k) { LongArray(m) { jin.nextInt().toLong() } }
        val sc = Scanner(System.`in`)
        val s = sc.next()
        val ones = IntArray(s.length + 1)
        val zeroes = IntArray(s.length + 1)
        zeroes[0] = 0
        ones[0] = zeroes[0]
        for (i in 0 until s.length) {
            ones[i + 1] = ones[i]
            zeroes[i + 1] = zeroes[i]
            if (s[i] == '1') ones[i + 1]++ else zeroes[i + 1]++
        }
        for (k in 1..s.length) {
            var start = 0
            var cntr = 0
            while (start < s.length) {
                var l = start
                var r = s.length - 1
                while (l != r) {
                    val mid = (l + r + 1) / 2
                    if (ones[mid + 1] - ones[start] <= k || zeroes[mid + 1] - zeroes[start] <= k) {
                        l = mid
                    } else {
                        r = mid - 1
                    }
                }
                start = l + 1
                //System.out.print(l + " ");
                cntr++
            }
            print("$cntr ")
        }
    }
