#include <deque>
#include <iostream>
#include <climits>
#include <limits>
#include <queue>
#include <sstream>
#include <vector>

struct Cell {
    long long time;
    int x, y;
    bool operator>(const Cell &other) const {
        return time > other.time;
    }
};

std::vector<std::vector<int>>* h;

const long long INF = 1e18;

std::vector<std::vector<long long>> bfs(int n, int m) {
    std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> pq;
    std::vector<std::vector<long long>> t(n, std::vector<long long>(m, LLONG_MAX));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (h->at(i)[j] == 0) {
                t[i][j] = 0;
                pq.push({0, i, j});
            }
        }
    }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!pq.empty()) {
        Cell c = pq.top(); pq.pop();
        int i = c.x, j = c.y;

        if (c.time > t[i][j]) continue;

        for (int d = 0; d < 4; d++) {
            int ni = i + dx[d];
            int nj = j + dy[d];
            if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;

            long long next_time = std::max(t[i][j], (long long)h->at(ni)[nj]);
            if (next_time < t[ni][nj]) {
                t[ni][nj] = next_time;
                pq.push({next_time, ni, nj});
            }
        }
    }

    return t;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    h = new std::vector<std::vector<int>>(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> h->at(i)[j];
        }
    }

    const std::vector<std::vector<long long>> t = bfs(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j > 0) std::cout << ' ';
            std::cout << t[i][j];
        }

        std::cout << std::endl;
    }

    return 0;
}