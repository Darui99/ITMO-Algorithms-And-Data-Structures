import java.io.File
import java.util.*

var cin = File("bridges.in").bufferedReader()
var cout = File("bridges.out").bufferedWriter()

var g: Array<MutableList<Pair<Int, Int>>> = Array(0, { i -> mutableListOf<Pair<Int, Int>>() })
var color: IntArray = IntArray(0)
var tin: IntArray = IntArray(0)
var up: IntArray = IntArray(0)
var br: BooleanArray = BooleanArray(0)

var timer: Int = 1

fun dfs(v: Int, p: Int) {
    color[v] = 1
    tin[v] = timer++
    up[v] = tin[v]
    for (edge in g[v]) {
        val to = edge.first
        val num = edge.second

        if (color[to] == 1 && num != p) {
            up[v] = Math.min(up[v], tin[to])

        }
        if (color[to] == 0) {
            dfs(to, num)
            up[v] = Math.min(up[v], up[to])
            if (up[to] > tin[v])
                br[num] = true
        }
    }
    color[v] = 2
}

fun main(args: Array<String>) {
    val (n, m) = cin.readLine()!!.split(" ").map { it.toInt() }

    g = Array(n, { i -> mutableListOf<Pair<Int, Int>>() })
    color = IntArray(n, { i -> 0 })
    tin = IntArray(n, { i -> 0 })
    up = IntArray(n, { i -> 0 })
    br = BooleanArray(m, { i -> false })

    for (i in 0 until m) {
        val (a, b) = cin.readLine()!!.split(" ").map { it.toInt() - 1 }
        g[a].add(Pair(b, i))
        g[b].add(Pair(a, i))
    }

    for (i in 0 until n) {
        if (color[i] == 0)
            dfs(i, -1)
    }

    var ans: MutableList<Int> = mutableListOf()

    for (i in 0 until m) {
        if (br[i])
            ans.add(i)
    }

    cout.write("${ans.size}\n")
    for (i in ans)
        cout.write("${i + 1} ")

    cin.close()
    cout.close()
}