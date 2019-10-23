import java.io.File
import java.util.*

var cin = File("bipartite.in").bufferedReader()
var cout = File("bipartite.out").bufferedWriter()

var g: Array<MutableList<Int>> = Array(0, { i -> mutableListOf<Int>() })
var color = IntArray(0)
var comp = IntArray(0)

var flag = true

fun dfs(v: Int, k: Int) {
    color[v] = 1
    comp[v] = k
    for (to in g[v]) {
        if (color[to] == 0)
            dfs(to, (k + 1) % 2)
        else if (comp[to] == comp[v])
            flag = false
    }
    color[v] = 2
}

fun main(args: Array<String>) {
    val (n, m) = cin.readLine()!!.split(" ").map { it.toInt() }

    g = Array(n, { i -> mutableListOf<Int>() })
    color = IntArray(n, { i -> 0 })
    comp = IntArray(n, { i -> 0 })

    for (i in 0 until m) {
        val (a, b) = cin.readLine()!!.split(" ").map { it.toInt() - 1 }
        g[a].add(b)
        g[b].add(a)
    }

    for (i in 0 until n) {
        if (color[i] == 0)
            dfs(i, 0)
    }

    if (flag)
        cout.write("YES")
    else
        cout.write("NO")

    cin.close()
    cout.close()
}