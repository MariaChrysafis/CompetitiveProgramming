import java.lang.AssertionError
private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
fun main(args: Array<String>) {
    val t = readLine()!!.toInt()
    for (i in 0 until t) {
        var (a, b, k) = readLine()!!.split(' ').map{ it.toLong() }
        if(k % 2 == 0.toLong()){
          println(k/2 * (a - b))
        }else{
          println(k/2 * (a - b) + a)
        }
    }
}
