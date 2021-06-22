import javafx.scene.layout.Priority
import java.util.*
import kotlin.collections.ArrayList
import kotlin.math.min
import kotlin.collections.HashMap
import kotlin.math.*
import kotlin.system.exitProcess
import java.io.*;
 
@JvmField val INPUT = System.`in`
@JvmField val OUTPUT = System.out
 
const val _BUFFER_SIZE = 1 shl 16
@JvmField val _buffer = ByteArray(_BUFFER_SIZE)
@JvmField var _bufferPt = 0
@JvmField var _bytesRead = 0
 
tailrec fun readChar(): Char {
    if(_bufferPt == _bytesRead) {
        _bufferPt = 0
        _bytesRead = INPUT.read(_buffer, 0, _BUFFER_SIZE)
    }
    return if(_bytesRead < 0) Char.MIN_VALUE
    else {
        val c = _buffer[_bufferPt++].toChar()
        if (c == '\r') readChar()
        else c
    }
}
 
fun readLine(): String? {
    var c = readChar()
    return if(c == Char.MIN_VALUE) null
    else buildString {
        while(true) {
            when(c) {
                '\n', Char.MIN_VALUE -> return@buildString
                else -> {
                    append(c)
                    c = readChar()
                }
            }
        }
    }
}
fun readLn() = readLine()!!
 
fun read() = buildString {
    var c = readChar()
    while(c <= ' ') {
        if(c == Char.MIN_VALUE) return@buildString
        c = readChar()
    }
    do {
        append(c)
        c = readChar()
    } while(c > ' ')
}
fun readInt() = read().toInt()
fun readDouble() = read().toDouble()
fun readLong() = read().toLong()
fun readStrings(n: Int) = List(n) { read() }
fun readLines(n: Int) = List(n) { readLn() }
fun readInts(n: Int) = List(n) { read().toInt() }
fun readIntArray(n: Int) = IntArray(n) { read().toInt() }
fun readDoubles(n: Int) = List(n) { read().toDouble() }
fun readDoubleArray(n: Int) = DoubleArray(n) { read().toDouble() }
fun readLongs(n: Int) = List(n) { read().toLong() }
fun readLongArray(n: Int) = LongArray(n) { read().toLong() }
 
fun main() {
    val map1 = mutableMapOf<Long, Long>()
    val n = readInt()
    val arr = readLongArray(n)
    var sum = 0.toLong();
    for(i in 0 until n){
        map1[arr[i]] = 0.toLong()
        sum = sum + arr[i]
    }
    
    for(i in 0 until n){
        map1[arr[i]] = (map1[arr[i]]!!.plus(1))!!.toLong()
    }
    
    var v = Vector<Int>();
    for(i in 0 until n){
        var newSum = sum - arr[i]
        if(newSum % 2 == 0.toLong()){
            if(map1[newSum/2] == null){
                continue
            }else if(map1[newSum/2] == 1.toLong()){
                if(newSum/2 != arr[i]){
                    v.add(i)
                }
            }else{
                v.add(i)
            }
        }
    }
    println(v.size)
    for(i in 0 until v.size){
        print(v[i] + 1)
        print(" ")
    }
 
}
