import java.util.*

val inf: Int = (1e9 + 7).toInt()

var g: Array< MutableList< Pair<Int, Int> > > = Array(0, { i -> mutableListOf< Pair<Int, Int> >()})
var color: IntArray = IntArray(0, { i -> 0 })
var topsort: MutableList<Int> = mutableListOf()

fun dfs(v: Int) {
    color[v] = 1
    for (to in g[v]) {
        if (color[to.first] == 0)
            dfs(to.first)
    }
    color[v] = 2
    topsort.add(v)
}

fun main(args: Array<String>) {
    val (n, m, s, t) = readLine()!!.split(" ").map { it.toInt() }

    g = Array(n, { i -> mutableListOf< Pair<Int, Int> >()})
    color = IntArray(n, { i -> 0})

    for (i in 0 until m) {
        val (a, b, c) = readLine()!!.split(" ").map { it.toInt() }
        g[a - 1].add(Pair(b - 1, c))
    }

    for (i in 0 until n) {
        if (color[i] == 0)
            dfs(i)
    }

    var dp = IntArray(n, { i -> inf})
    dp[s - 1] = 0

    for (i in n - 1 downTo 0) {
        val v = topsort[i]
        if (dp[v] == inf)
            continue
        for (edge in g[v]) {
            dp[edge.first] = Math.min(dp[edge.first], dp[v] + edge.second)
        }
    }

    if (dp[t - 1] == inf)
        print("Unreachable")
    else
        print(dp[t - 1])
}