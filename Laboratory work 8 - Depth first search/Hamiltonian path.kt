import java.util.*

var g: Array<MutableList<Int>> = Array(0, { i -> mutableListOf<Int>()})
var color: IntArray = IntArray(0, { i -> 0 })
var topsort: MutableList<Int> = mutableListOf()

fun dfs(v: Int) {
    color[v] = 1
    for (to in g[v]) {
        if (color[to] == 0)
            dfs(to)
    }
    color[v] = 2
    topsort.add(v)
}

fun main(args: Array<String>) {
    val (n, m) = readLine()!!.split(" ").map { it.toInt() }
    
    if (n == 1) {
        print("YES")
        return
    }

    g = Array(n, { i -> mutableListOf<Int>()})
    color = IntArray(n, { i -> 0})

    for (i in 0 until m) {
        val (a, b) = readLine()!!.split(" ").map { it.toInt() - 1 }
        g[a].add(b)
    }

    for (i in 0 until n) {
        if (color[i] == 0)
            dfs(i)
    }

    var dp = IntArray(n, { i -> 1})
    for (i in n - 1 downTo 0) {
        val v = topsort[i]
        for (to in g[v]) {
            dp[to] = Math.max(dp[to], dp[v] + 1)
            if (dp[to] == n) {
                print("YES")
                return
            }
        }
    }

    print("NO")
}