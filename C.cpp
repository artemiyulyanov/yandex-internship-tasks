#include <iostream>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;

    std::vector<std::vector<std::string>> queries(N+1); // 1-based

    DisjointSet ds(N);
    std::unordered_map<std::string, int> word_to_query;

    for (int i = 1; i <= N; i++) {
        int M;
        std::cin >> M;
        queries[i].resize(M);
        for (int j = 0; j < M; j++) {
            std::cin >> queries[i][j];
            std::string &word = queries[i][j];

            if (word_to_query.count(word)) {
                ds.unite(i, word_to_query[word]);
            } else {
                word_to_query[word] = i;
            }
        }
    }

    std::unordered_map<int, std::unordered_set<std::string>> context_words;

    for (int i = 1; i <= N; i++) {
        int root = ds.get(i);
        for (auto &word : queries[i]) {
            context_words[root].insert(word);
        }
    }

    int num_contexts = context_words.size();
    int max_size = 0;

    for (auto &p : context_words) {
        max_size = std::max(max_size, (int)p.second.size());
    }

    std::cout << num_contexts << " " << max_size << "\n";
    return 0;
}