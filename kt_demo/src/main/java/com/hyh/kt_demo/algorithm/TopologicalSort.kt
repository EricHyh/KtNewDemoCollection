package com.hyh.kt_demo.algorithm

/**
 * 拓扑排序
 *
 * @author eriche 2024/4/10
 */
class TopologicalSort<T> constructor() {

    // 存储有向图
    private lateinit var edges: MutableMap<T, MutableList<T>>

    // 存储环
    private lateinit var circularDependencies: MutableList<List<T>>

    // 标记每个节点的状态：0=未搜索，1=搜索中，2=已完成
    private lateinit var visited: MutableMap<T, Int>

    // 用数组来模拟栈，下标 n-1 为栈底，0 为栈顶
    private lateinit var result: MutableList<T>

    // 判断有向图中是否有环
    private var valid = true

    fun findOrder(nodes: List<T>, dependencies: List<Pair<T, T>>): Pair<List<T>, List<List<T>>> {
        edges = mutableMapOf()
        visited = mutableMapOf()
        for (node in nodes) {
            edges[node] = ArrayList()
            visited[node] = 0
        }
        circularDependencies = mutableListOf()
        result = mutableListOf()

        for (dependency in dependencies) {
            val first: T = dependency.first //依赖方
            val second: T = dependency.second //被依赖方
            edges[second]!!.add(first)
        }
        // 每次挑选一个「未搜索」的节点，开始进行深度优先搜索
        var i = 0
        while (i < nodes.size && valid) {
            val node = nodes[i]
            if (visited[node] == 0) {
                dfs(node, mutableListOf())
            }
            ++i
        }

        return result to circularDependencies
        // 如果没有环，那么就有拓扑排序
    }

    private fun dfs(u: T, pre: MutableList<T>) {
        // 将节点标记为「搜索中」
        visited[u] = 1

        // 搜索其相邻节点
        for (v in edges[u]!!) {
            // 如果「未搜索」那么搜索相邻节点
            if (visited[v] == 0) {
                pre.add(u)
                dfs(v, pre)
            } else if (visited[v] == 1) {
                //pre、u、v
                circularDependencies.add(mutableListOf<T>().apply {
                    this.add(v)
                    this.add(u)
                    val index = pre.indexOf(v)
                    if (index >= 0) {
                        this.addAll(pre.subList(index, pre.size).reversed())
                    }
                })
            }
        }

        // 将节点标记为「已完成」
        visited[u] = 2
        // 将节点入栈
        result.add(0, u)
    }
}