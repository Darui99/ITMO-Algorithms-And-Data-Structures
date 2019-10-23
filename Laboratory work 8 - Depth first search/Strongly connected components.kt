import java.util.*

var g: Array<MutableList<Int>> = Array(0, { i -> mutableListOf<Int>()})
var tr_g = g.copyOf()
var color: IntArray = IntArray(0, { i -> 0 })
var comp = color.copyOf()
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

var cur_comp: Int = 0

fun tr_dfs(v: Int) {
    color[v] = 1
    comp[v] = cur_comp
    for (to in tr_g[v]) {
        if (color[to] == 0)
            tr_dfs(to)
    }
    color[v] = 2
}

fun main(args: Array<String>) {
    val (n, m) = readLine()!!.split(" ").map { it.toInt() }

    g = Array(n, { i -> mutableListOf<Int>()})
    tr_g = Array(n, { i -> mutableListOf<Int>()})
    color = IntArray(n, { i -> 0})
    comp = IntArray(n, { i -> -1})

    for (i in 0 until m) {
        val (a, b) = readLine()!!.split(" ").map { it.toInt() - 1 }
        g[a].add(b)
        tr_g[b].add(a)
    }

    for (i in 0 until n) {
        if (color[i] == 0)
            dfs(i)
    }

    color = color.map { i: Int -> 0 }.toIntArray()

    for(i in n - 1 downTo 0) {
        if (color[topsort[i]] == 0) {
            tr_dfs(topsort[i])
            cur_comp++
        }
    }

    println(cur_comp)
    for (i in comp)
        print("${i + 1} ")
}