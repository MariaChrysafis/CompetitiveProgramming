import java.io.*
import java.util.*

fun main() {
    repeat(readLine()!!.toInt()) {
        val (n, m) = readLine()!!.split(" ").map { it.toInt() }
        println(n + m)
    }
}
