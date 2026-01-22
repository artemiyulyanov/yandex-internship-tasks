#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

struct DisjointSet {
    int n;
    std::vector<int> parents; // 1-based
    std::vector<int> ranks; // 1-based

    DisjointSet(int n) : n(n), parents(n+1), ranks(n+1, 0) {
        std::iota(std::begin(parents), std::end(parents), 0);
    }

    int get(int x) {
        if (parents[x] != x) {
            parents[x] = get(parents[x]);
        }

        return parents[x];
    }

    void unite(int x, int y) {
        x = get(x);
        y = get(y);

        if (x == y) return;
        if (ranks[x] == ranks[y]) ranks[x]++;

        if (ranks[x] < ranks[y]) {
            parents[x] = y;
        } else if (ranks[x] > ranks[y]) {
            parents[y] = x;
        }
    }
};

const int MAXN = 100005;

std::vector<int> adj[MAXN];
int tin[MAXN], low[MAXN];
bool visited[MAXN];
int timer;

std::vector<std::pair<int,int>> bridges;

void dfs(int v, int parent) {
    visited[v] = true;
    tin[v] = low[v] = timer++;

    for (int to : adj[v]) {
        if (to == parent) continue;

        if (visited[to]) {
            low[v] = std::min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = std::min(low[v], low[to]);

            if (low[to] > tin[v]) {
                bridges.emplace_back(v, to);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::set<std::pair<int,int>> existing_edges;

    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);

        if (u > v) std::swap(u,v);
        existing_edges.insert({u,v});
    }

    timer = 1;
    for (int i=1;i<=n;i++) if (!visited[i]) dfs(i,-1);

    DisjointSet dsu(n);
    std::set<std::pair<int,int>> bridge_set;

    for (auto &[u,v]: bridges){
        if (u>v) std::swap(u,v);
        bridge_set.insert({u,v});
    }

    for (int v=1; v<=n; v++) {
        for (int to: adj[v]) {
            int a=v, b=to; if(a>b) std::swap(a,b);
            if (bridge_set.count({a,b})) continue;
            dsu.unite(a,b);
        }
    }

    // Находим листья дерева мостов
    std::map<int,int> deg; // степень в графе мостов
    std::map<int,int> rep_to_vertex; // для выбора любой вершины блока

    for (int i=1;i<=n;i++) rep_to_vertex[dsu.get(i)] = i;

    for (auto &[u,v]: bridges){
        int a = dsu.get(u);
        int b = dsu.get(v);
        deg[a]++; deg[b]++;
    }

    std::vector<int> leaves;
    for (auto &[block, d] : deg) {
        if (d == 1) leaves.push_back(block);
    }

    int k = (leaves.size()+1)/2;
    std::cout << k << "\n";

    for (int i=0;i+1<leaves.size();i+=2){
        int u = rep_to_vertex[leaves[i]];
        int v = rep_to_vertex[leaves[i+1]];

        if(u > v) std::swap(u,v);

        if (existing_edges.count({u,v})) {
            v = rep_to_vertex[leaves[i+1]];
        }

        std::cout << u << " " << v << "\n";
    }

    if (leaves.size()%2 == 1){
        int u = rep_to_vertex[leaves.back()];
        int v = rep_to_vertex[leaves[0]];
        if (u > v) std::swap(u,v);
        if (existing_edges.count({u,v})) v = rep_to_vertex[leaves[0]];
        std::cout << u << " " << v << "\n";
    }

    return 0;
}