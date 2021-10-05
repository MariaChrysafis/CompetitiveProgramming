import java.util.*
import java.io.*

    fun solve(n: Int, m: Int, arr: Array<IntArray>) {
        val g = Graph(arr)
        //System.out.println(arr);
        var fine = true
        var cnt = 0
        for (i in 0 until n) {
            for (j in 0 until m) {
                if (arr[i][j] != 0) cnt++
                if (arr[i][j] != 0 && fine) {
                    g.dfs(i, j)
                    fine = false
                }
            }
        }
        for (i in 0 until n) {
            for (j in 0 until m) {
                if (arr[i][j] != 0 && !g.hasVisited[i][j]!!) {
                    println("-1")
                    return
                }
            }
        }
        val grid = Array(cnt) { IntArray(cnt) }
        for (i in 0 until cnt) {
            for (j in 0 until cnt) {
                grid[i][j] = g.vec[i + j]
            }
        }
        println(grid.size.toString() + " " + grid[0].size)
        for (i in grid.indices) {
            for (j in 0 until grid[0].size) {
                print(grid[i][j].toString() + " ")
            }
            println()
        }
    }

    fun main(args: Array<String>) {
        //val positions = Array(k) { LongArray(m) { jin.nextInt().toLong() } }
        val sc = Scanner(System.`in`)
        val t = sc.nextInt()
        for (tc in 1..t) {
            val n = sc.nextInt()
            val m = sc.nextInt()
            val arr = Array(n) { IntArray(m) }
            for (i in 0 until n) {
                for (j in 0 until m) {
                    arr[i][j] = sc.nextInt()
                }
            }
            solve(n, m, arr)
        }
    }

    class Graph(var arr: Array<IntArray>) {
        var hasVisited: Array<Array<Boolean?>>
        var vec = ArrayList<Int>()
        fun dfs(x: Int, y: Int) {
            vec.add(arr[x][y])
            hasVisited[x][y] = true
            for (dx in -1..1) {
                for (dy in -1..1) {
                    if (Math.abs(dx) + Math.abs(dy) == 1) {
                        val newX = x + dx
                        val newY = y + dy
                        if (newX >= 0 && newX < arr.size && newY >= 0 && newY < arr[0].size) {
                            if (!hasVisited[newX][newY]!!) {
                                dfs(newX, newY)
                                vec.add(arr[x][y])
                            }
                        }
                    }
                }
            }
        }

        init {
            val new_arr = Array(arr.size) {
                arrayOfNulls<Boolean>(
                    arr[0].size
                )
            }
            for (i in new_arr.indices) {
                for (j in 0 until new_arr[i].size) {
                    new_arr[i][j] = false
                }
            }
            hasVisited = new_arr
            for (i in arr.indices) {
                for (j in 0 until arr[0].size) {
                    if (arr[i][j] == 0) {
                        hasVisited[i][j] = true
                    }
                }
            }
        }
    }
